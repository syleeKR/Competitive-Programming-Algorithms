
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5+1;
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

//node 값 1씩 증가(구간 업데이트) + 구간의 합 지원

struct segtree
{
    int size;
    vll operations;
    vll values;
    
    ll NO_OPERATIONS = LLONG_MAX;
    ll NEUTRAL_ELEMENT = 0;
    
    ll modify_op(ll a, ll b, ll len)        //sum
    {
        if(b==NO_OPERATIONS)return a;
        if(a!=NO_OPERATIONS)return a+b*len;
        else return b*len;
    }
    ll calc_op(ll a, ll b)         //sum
    {
        return a+b;
    }
    void apply_mod_op(ll & a, ll b, ll len)
    {
        a = modify_op(a,b,len);
    }
    
    void propagate(int x, int lx, int rx)
    {
        if(rx-lx==1)return;         //at leaf. do not propagate
        apply_mod_op(values[2*x+1], operations[x],(rx-lx)/2);
        apply_mod_op(operations[2*x+1], operations[x],1);
        apply_mod_op(values[2*x+2], operations[x],(rx-lx)/2);
        apply_mod_op(operations[2*x+2], operations[x],1);
        operations[x] = NO_OPERATIONS;
    }
    
    
    
    
    void init(int n)
    {
        size=1;
        while(size<n)size*=2;
        operations.resize(size*2, NO_OPERATIONS);
        values.resize(size*2,0LL);
    }
    
    void modify(int l, int r, int v, int x, int lx, int rx)
    {
        propagate(x,lx,rx);
        if(rx<=l || lx>=r)return;
        if(l<=lx && rx<=r )
        {
            apply_mod_op(operations[x] , v,1);
            apply_mod_op(values[x], v,rx-lx);
            return;
        }
        int m = (lx+rx)/2;
        modify(l,r,v, 2*x+1, lx, m);
        modify(l,r,v,2*x+2, m, rx);
        values[x] = calc_op(values[2*x+1], values[2*x+2]);
    }
    
    void modify(int l, int r, int v)
    {
        modify(l, r, v, 0, 0, size);
    }
    
    
    ll calc(int l, int r, int x, int lx, int rx)
    {
        propagate(x, lx, rx);
        if(rx<=l || lx>=r)return NEUTRAL_ELEMENT;
        if(l<=lx && rx<=r )
        {
            return values[x];
        }
        int m = (lx+rx)/2;
        ll v1 = calc(l,r, 2*x+1, lx, m);
        ll v2 = calc(l,r, 2*x+2, m, rx);
        return calc_op(v1,v2);
    }
    
    
    ll calc(int l, int r)
    {
        return calc(l,r,0, 0, size);
    }
    
}st;


vint adj[MxN];
// dfs //
vint child[MxN];         //obeying heavy light decomposition order
// dfs1 //
int treesize[MxN];
int depth[MxN];
int parent[MxN];
// dfs2 //
int indexof[MxN];          //location in tree_traversal_array
int topofchain[MxN];
vint tree_traversal_array; //obeying heavy light decomposition order
//      //

void dfs(int p, int c)         //build child
{
    for(auto node :  adj[c])
    {
        if(node!=p)
        {
            child[c].pb(node);
            dfs(c,node);
        }
    }
}

void dfs1(int node)            //build treesize, parent, depth
{
    treesize[node]++;
    for(auto &next : child[node])
    {
        parent[next]=node;
        depth[next] = depth[node]+1;
        dfs1(next);
        treesize[node]+=treesize[next];
        if(treesize[next]>treesize[child[node][0]]) swap(next, child[node][0]);    //always child[node][0] corresponds to the heavy chain
    }
}

void dfs2(int node)            //build tree_traversal_array, topofchain
{
    indexof[node] = (int)tree_traversal_array.size();
    tree_traversal_array.pb(node);
    
    if(node==1)topofchain[node]=1;
    
    for(auto next : child[node])
    {
        topofchain[next] = (next==child[node][0])?topofchain[node]:next;
        dfs2(next);
    }
}

void modify(int u, int v, int val)
{
    while(topofchain[u]!=topofchain[v])
    {
        if(depth[topofchain[u]]<depth[topofchain[v]])swap(u,v);  //u가 더 depth큼
        int top  = topofchain[u];
        st.modify(indexof[top],indexof[u]+1,1);
        u = parent[topofchain[u]];
    }
    if(depth[u]<depth[v])swap(u,v);
    st.modify(indexof[v], indexof[u]+1,1);
}

ll calc(int u, int v)
{
    ll ans=0;
    
    while(topofchain[u]!=topofchain[v])
    {
        if(depth[topofchain[u]]<depth[topofchain[v]])swap(u,v);  //u가 더 depth큼
        int top  = topofchain[u];
        ans += st.calc(indexof[top],indexof[u]+1);
        u = parent[topofchain[u]];
    }
    if(depth[u]<depth[v])swap(u,v);
    ans +=  st.calc(indexof[v], indexof[u]+1);
    return ans;
}


void solve()
{
    int n,m; cin>>n>>m;
    
    REP0(i,n-1)
    {
        int u, v; cin>>u>>v;
        adj[u].pb(v); adj[v].pb(u);
    }
    dfs(0,1);
    dfs1(1);
    dfs2(1);
    
    st.init(n);
    
    while(m--)
    {
        char op; cin>>op;
        if(op=='P')
        {
            int u, v; cin>>u>>v;
            modify(u,v, 1);
        }
        else{
            int u, v; cin>>u>>v;
            cout<<calc(u,v)<<endl;
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

