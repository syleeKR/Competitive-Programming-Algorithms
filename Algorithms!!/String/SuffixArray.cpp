#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9+7;
const int MxN = 1e5;
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
#define PI M_PI


void counting_sort(vint & p, vint & c)
{
    int n = sz(p);
    vint cnt(n);
    vint pos(n);

    for(auto x : c)cnt[x]++;
    pos[0]=0;
    for(int i=1; i<n; i++)pos[i] = pos[i-1]+cnt[i-1];

    vint p_update(n);
    for(auto x: p)
    {
        p_update[pos[c[x]]] = x;
        pos[c[x]]++;
    }
    p  = p_update;
}


pair<vint, vint> suffix_lcp_array(string s)  //build suffix array in O(nlogn), lcp in O(n)
{
    s += "$";
    int n = sz(s);
    vint p(n), c(n);

    vector<pair<char, int>> temp(n);
    REP0(i,n)temp[i] = {s[i], i};
    sort(all(temp));
    REP0(i,n)p[i]=temp[i].se;
    c[p[0]]=0;
    REP1(i,n-1)
    {
        if(temp[i].fi!=temp[i-1].fi)c[p[i]]=c[p[i-1]]+1;
        else c[p[i]]=c[p[i-1]];
    }

    int k=0;
    while((1<<k) < n)
    {
        REP0(i,n)p[i] = (p[i]-(1<<k)+n)%n;

        counting_sort(p,c);

        vint c_update(n);
        c_update[p[0]]=0;
        REP1(i,n-1)
        {
            pii prev = {c[p[i-1]], c[(p[i-1] + (1<<k))%n]};
            pii curr = {c[p[i]], c[(p[i] + (1<<k))%n]};
            if(prev!=curr)c_update[p[i]]=c_update[p[i-1]]+1;
            else c_update[p[i]]=c_update[p[i-1]];
        }
        c = c_update;
        k ++;
    }


    vint lcp(n);
    int skip = 0;
    for(int i=0; i<n-1; i++)
    {
        int pi = c[i];
        int j = p[pi - 1];
        while(s[i+skip]==s[j+skip])skip++;

        lcp[pi] = skip;
        skip=max(skip-1,0);
    }



    return {p, lcp};
    // suffix array : p
    //lcp array : lcp
}


void solve()
{
    int n; cin>>n;

    string s; cin>>s;

    vint lcp = suffix_lcp_array(s).se;

    int ans = 0;

    REP(i,2,sz(lcp)-1)
    {
        ans = max(ans, lcp[i]);
    }
    cout<<ans<<endl;

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
