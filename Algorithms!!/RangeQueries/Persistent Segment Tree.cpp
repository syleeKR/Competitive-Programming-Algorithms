
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long ld;
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

struct Node
{
    int lchild,rchild;
    ll value;
    Node(){lchild=rchild=-1; value=0;}
};


struct segtree
{
    int size;
    int curr;
    vector<int> rootindex;
    vector<Node> nodes;
    
    void init(int n, int q)
    {
        curr=1;
        size=1;
        while(size<n)size*=2;
        rootindex.pb(0);
        nodes.resize(2*size + q * ((int)log2(2*size)+1) );
    }
    
    void build(vint &v, int x, int lx, int rx)
    {
        if(rx-lx==1)
        {
            if(lx<sz(v))nodes[x].value = v[lx];
            return;
        }
        int m=(lx+rx)/2;
        nodes[x].lchild = curr;
        curr++;
        nodes[x].rchild =curr;
        curr++;

        build(v, nodes[x].lchild, lx,m);
        build(v,nodes[x].rchild, m, rx);
        nodes[x].value = nodes[nodes[x].lchild].value + nodes[nodes[x].rchild].value;
    }
    void build(vint &v)
    {
        build(v,0,0, size);
    }
    
    ll calc(int l, int r, int x, int lx, int rx)
    {
        if(rx<=l || r<=lx)return 0;
        if(l<=lx && rx<=r)return nodes[x].value;
        int m=(lx+rx)/2;
        return calc(l,r,nodes[x].lchild, lx,m)+calc(l,r,nodes[x].rchild, m, rx);
    }
    
    ll calc(int l, int r, int k)   //k번째 tree
    {
        return calc(l,r, rootindex[k], 0,size);
    }
    
    void set(int i, int v, int prev, int x, int lx, int rx)
    {
        if(rx-lx==1){nodes[x].value = v+(nodes[prev].value);return;}
        int m=(lx+rx)/2;
        if(i<m)
        {
            nodes[x].lchild = curr;
            curr++;
            nodes[x].rchild = nodes[prev].rchild;
            set(i,v,nodes[prev].lchild, nodes[x].lchild, lx,m);
        }
        else{
            nodes[x].rchild = curr;
            curr++;
            nodes[x].lchild = nodes[prev].lchild;
            set(i,v,nodes[prev].rchild, nodes[x].rchild, m, rx);
        }
        nodes[x].value= nodes[nodes[x].lchild].value+ nodes[nodes[x].rchild].value;
        
    }
   
    
    void set(int i, int v)   //v 만큼 증가
    {
        rootindex.pb(curr);
        curr++;
        set(i,v,rootindex[sz(rootindex)-2], rootindex[sz(rootindex)-1], 0,size);
    }
    
};


void solve()
{
    
}





int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t; cin>>t;  //t=1;
    while(t--)
    {
        solve();
    }
}
