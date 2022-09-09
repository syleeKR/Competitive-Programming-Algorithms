
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5;
const int MxK = 1e9;
const ll inf = INT_MAX;
#define REP0(i,n) for(int i=0; i<n; i++)
#define REP1(i,n) for(int i=1; i<=n; i++)
#define REP(i,a,b) for(int i=a; i<=b; i++)
#define pb push_back
#define fi first
#define se second
#define reset(X) memset(X, 0, sizeof(X))
#define pii pair<int, int>
#define endl "\n"
#define vint vector<int>
#define pll pair<ll, ll>
#define vll vector<ll>
#define LOG 18 //enough for 10^5


struct segtree
{
    int size;
    vector<vint> values;
    
    void init(int n)
    {
        size=1;
        while(size<n)size*=2;
        values.resize(size*2);
    }
    
    
    
    void build(vint &v, int x, int lx, int rx)
    {
        if(rx-lx==1)
        {
            if (lx<v.size()){
            values[x].pb( v[lx]);
            }
            return;
        }
        int m = (lx+rx)/2;
        build(v,2*x+1, lx, m);
        build(v, 2*x+2, m, rx);
        values[2*x+1].pb(inf);
        values[2*x+2].pb(inf);
        int lpoint=0; int rpoint=0;
        while(lpoint<values[2*x+1].size()-1 || rpoint<values[2*x+2].size()-1)
        {
            if(values[2*x+1][lpoint]<values[2*x+2][rpoint])
            {
                values[x].pb(values[2*x+1][lpoint]);
                lpoint++;
            }
            else
            {
                values[x].pb(values[2*x+2][rpoint]);
                rpoint++;
            }
        }
        values[2*x+1].pop_back();
        values[2*x+2].pop_back();
    }
    
    void build(vector<int> &v)
    {
        build(v, 0, 0, size);
    }
    

    int calc(int l, int r, int k, int x, int lx, int rx)
    {
        if (lx>=r || rx<=l)return 0;   //neutral element
        if (l<=lx && rx<=r)
        {
            int count=0;
            int left=0; int right=(int)values[x].size()-1;
            while(right>=left)
            {
                if(right==left)
                {
                    if(values[x][left]>k)count++;
                    break;
                }
                int m = (left+right)/2;
                if(values[x][m]<=k)left=m+1;
                else{
                    count+=right-m;
                    right = m;
                }

            }

            
            return count;
        }
        
        int m = (lx+rx)/2;
        return calc(l,r,k,2*x+1, lx,m) + calc(l,r,k,2*x+2, m,rx);
        
        
    }
    
    int calc(int l, int r, int k)
    {
        return calc(l,r,k, 0, 0, size);
    }
};


void solve()
{
    int n; cin>>n;
    vint v(n);
    REP0(i,n)cin>>v[i];
    
    segtree st;
    st.init(n);
    st.build(v);
    
    int m; cin>>m;
    while(m--)
    {
        int l, r, k; cin>>l>>r>>k;
        cout<<st.calc(l-1,r,k)<<endl;
    }
}





int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t; t=1;
    while(t--)
    {
        solve();
    }
}



