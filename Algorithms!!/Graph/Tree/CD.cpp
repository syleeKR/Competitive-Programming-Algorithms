
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9+7;
const int MxN = 5e4;
const int inf = INT_MAX;
#define REP0(i,n) for(int i=0; i<n; i++)
#define REP1(i,n) for(int i=1; i<=n; i++)
#define REP(i,a,b) for(int i=a; i<=b; i++)
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define reset(X) memset(X, 0, sizeof(X))
#define pb push_back
#define fi first
#define se second
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vint vector<int>
#define vll vector<ll>
#define vpii vector<pair<int, int>>
#define endl "\n"
#define LOG 18
//#define PI M_PI
typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = (int)a.size();
    if (n == 1)            //Base Case:n=1
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];   //짝수항
        a1[i] = a[2*i+1];   //홀수항
    }
    //recursion to base case
    fft(a0, invert);
    fft(a1, invert);

    //합치기, wn=e^(2pi/n)
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            //2^log(n) = n 으로 나누는 결과가 됨.
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}


vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    
    // 가장 가까운 2^k 꼴의 n으로 크기를 정해줌.
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // fft : coefficient rep to value rep : O(nlogn)
    fft(fa, false);
    fft(fb, false);
    // value rep에서 곱하기 : O(n)
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    //Inverse FFT : value rep to coefficeint rep :O(nlogn)
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}



bool isprime[2*MxN+1];
vint adj[MxN+1];
int centroid;
ll ans=0;

void preprocess()
{
    for(int i=2; i<=2*MxN; i++)isprime[i]=true;
    REP(i, 2, 2*MxN)
    {
        if(isprime[i])
        {
            int val = 2*i;
            while(val<=2*MxN)
            {
                isprime[val]=false;
                val+=i;
            }
        }
    }
}

int treesize[MxN+1];
bool marked[MxN+1];

void dfs_treesize(int p, int c)
{
    treesize[c] =1;
    for(auto next : adj[c])
    {
        if(next!=p && marked[next]==false)
        {
            dfs_treesize(c, next);
            treesize[c] += treesize[next];
        }
    }
}

void dfs_centroid(int p, int c, int subtreesize)
{
    bool iscentroid  = true;
    for(auto next : adj[c])
    {
        if(next!=p && marked[next]==false)
        {
            dfs_centroid(c, next, subtreesize);
            if(treesize[next]>subtreesize/2)iscentroid=false;
        }
    }
    if(treesize[c]<subtreesize/2)iscentroid=false;
    if(iscentroid)centroid =c;
}

vint temp;
int depth[MxN+1];
void dfs(int p, int c)
{
    if(sz(temp)<=depth[c]){
        temp.pb(1);
    }
    else temp[depth[c]]++;
    for(auto next : adj[c])
    {
        if(next !=p && marked[next]==false)
        {
            depth[next] = depth[c] +1;
            dfs(c, next);
        }
    }
}

void centroid_decomposition(int start)
{
    dfs_treesize(0, start);
    dfs_centroid(0, start, treesize[start]);
    marked[centroid] = true;
    vint v;
    v.pb(1); // centroid : dist =0;
    for(auto x : adj[centroid])
    {
        if(marked[x]==false)
        {
            temp.pb(0);
            depth[x] = 1;
            dfs(0, x);
            vint temp2 = multiply(temp, v);
            REP0(i, sz(temp2))
            {
                if(isprime[i])ans += temp2[i];
            }
            //여기서 merge temp
            for(int i=0; i<sz(temp); i++)
            {
                if(i>=sz(v))v.pb(temp[i]);
                else v[i]+=temp[i];
            }
            
            temp.clear();
        }
    }
    
    for(auto x : adj[centroid])
    {
        if(marked[x]==false)
        {
            centroid_decomposition(x);
        }
    }
}

void solve()
{
    preprocess();
    int n; cin>>n;
    REP0(i,n-1)
    {
        int u, v; cin>>u>>v;
        adj[u].pb(v); adj[v].pb(u);
    }
    
    
    centroid_decomposition(1);
    

    
    cout<< fixed<< setprecision(7)<<(ld)ans / ((ll)n*(n-1)/2) <<endl;
    
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t;t=1;
    while(t--)
    {
        solve();
    }
}


