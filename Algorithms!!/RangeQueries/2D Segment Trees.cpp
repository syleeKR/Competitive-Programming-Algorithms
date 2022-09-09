
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

struct segtree
{
    int size;
    vint values;
    
    void init(int n)
    {
        size=1;
        while(size<n)size*=2;
        values.resize(size*2);
    }
    void build(vint & v, int x, int lx, int rx)
    {
        if(rx-lx==1)
        {
            if(lx<sz(v))values[x] = v[lx];
            return;
        }
        int m =(lx+rx)/2;
        build(v, 2*x+1, lx, m);
        build(v,2*x+2, m, rx);
        values[x] = values[2*x+1] + values[2*x+2];
    }
    
    void build(vint & v)
    {
        build(v, 0,0, size);
    }
    
    
    void build(segtree &s1, segtree & s2)
    {
        vint temp;
        for(int i=s1.size-1; i<2*s1.size-1; i++)
        {
            temp.pb(s1.values[i]+s2.values[i]);
        }
        build(temp);
    }
    
    void set(int i, int val, int x, int lx, int rx)
    {
        if(rx-lx==1){values[x] = val;return;}
        int m=lx+rx>>1;
        if(i<m)set(i,val, 2*x+1, lx,m);
        else set(i, val, 2*x+2, m, rx);
        values[x] = values[2*x+1] + values[2*x+2];
    }
    
    
    void set(int i, int val)
    {
        set(i,val, 0,0,size);
    }
    
    void set(int i, segtree & s1, segtree & s2, int x, int lx, int rx)
    {
        if(rx-lx==1){values[x] = s1.values[x]+s2.values[x]; return;}
        int m=lx+rx>>1;
        if(i<m)set(i,s1,s2, 2*x+1, lx,m);
        else set(i, s1,s2, 2*x+2, m, rx);
        values[x] = values[2*x+1] + values[2*x+2];
    }
    
    void set(int i, segtree& s1, segtree & s2)
    {
        set(i, s1, s2, 0,0, size);
    }
    
    int calc(int l, int r, int x, int lx, int rx)
    {
        if(l<=lx && rx<=r)return values[x];
        if(rx<=l || r<=lx)return 0;
        int m=lx+rx>>1;
        return calc(l,r,2*x+1, lx, m) + calc(l,r,2*x+2, m, rx);
    }
    
    int calc(int l, int r)
    {
        return calc(l,r,0,0,size);
    }
};

struct segtree2d      //O(n^2)n build time, O(log^2 n) query time.
{
    int size;
    vector<segtree> values;
    
    void init(int n)
    {
        size =1;
        while(size<n)size *=2;
        values.resize(size*2);
    }
    
    void build(vector<vint> & v, int x, int lx, int rx)
    {
        if(rx-lx==1)
        {
            if(lx<sz(v))
            {
                values[x].build(v[lx]);
            }
            return;
        }
        int m=lx+rx>>1;
        build(v,2*x+1, lx,m);
        build(v, 2*x+2, m, rx);
        values[x].build(values[2*x+1], values[2*x+2]);
    }
    
    void build(vector<vint> & v)
    {
        for(auto &x : values)
        {
            x.init(sz(v[0]));
        }
        build(v, 0,0,size);
    }
    
    void set(int xcoord, int ycoord, int val, int x, int lx, int rx)
    {
        if(rx-lx==1)
        {
            values[x].set(xcoord, val);
            return;
        }
        int m=lx+rx>>1;
        if(ycoord<m)set(xcoord, ycoord, val, 2*x+1, lx,m);
        else set(xcoord, ycoord, val, 2*x+2, m, rx);
        values[x].set(xcoord,values[2*x+1], values[2*x+2]);
    }
    
    void set(int xcoord, int ycoord, int val)
    {
        set(xcoord, ycoord, val, 0,0,size);
    }
    
    int calc(int l, int r, int t, int b, int x, int lx, int rx)
    {
        if(t<=lx && rx<=b){return values[x].calc(l,r);}
        if(b<=lx || rx<=t)return 0;
        int m=lx+rx>>1;
        return calc(l,r,t,b,2*x+1, lx,m)+calc(l,r,t,b,2*x+2, m, rx);
    }
    
    
    int calc(int l, int r, int t, int b)
    {
        return calc(l,r,t,b, 0, 0, size);
    }
};

vector<vint> ar;


void solve()
{
    int n,m; cin>>n>>m;
    REP1(i, n)
    {
        vint temp;
        REP1(j,n)
        {
            int x; cin>>x;temp.pb(x);
        }
        ar.pb(temp);
    }
    
    segtree2d st2;
    st2.init(n);
    st2.build(ar);
        
    
    while(m--)
    {
        int op; cin>>op;
        if(op==0)
        {
            int x,y,val; cin>>x>>y>>val;
            st2.set(y-1,x-1,val);
        }
        else{
            int l,t,r,b; cin>>l>>t>>r>>b;
            cout<< st2.calc(t-1,b,l-1,r)<<endl;
        }
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

