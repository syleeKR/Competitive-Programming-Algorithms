
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
const int LOG = 17;   //upper bound of logN for this problem
int depth[MxN];
vint adj[MxN];


void dfs(int p, int child)
{
    for(auto x : adj[child])
    {
        if (x!=p)
        {
            depth[x]=depth[child]+1;
            dfs(child, x);
        }
    }
}




void solve()
{
    int n; cin>>n;
    int parent[n+1][LOG];    //sparse table. find LCA in O(log(n)) per query with O(nlogn) preprocessing
    REP0(i,n+1)parent[i][0]=0;
    REP1(i,n)
    {
        adj[i].clear();
    }
    REP0(i,n-1)
    {
        int u,v; cin>>u>>v;
        parent[v][0]=u;
        adj[v].pb(u);
        adj[u].pb(v);
    }
    
    
    
    //preprocessing sparse table.
    for (int k=1; k<LOG; k++)    //2^k th ancestor
    {
        parent[0][k]=0;
        for (int i=1; i<=n; i++)
        {
      
            parent[i][k] = parent[parent[i][k-1]][k-1];
        }
    }
    //find root
    int root=1;
    while(parent[root][0]!=0)
    {
        root=parent[root][0];
    }
    //run dfs to get depth
    depth[root]=0;
    dfs(0,root);
    
    //find lca
    
    int a,b; cin>>a>>b;
    
    if (depth[a]>depth[b]) swap(a,b);
    
    int diff =(depth[b]-depth[a]);
    for(int i=0; i<LOG; i++)
    {
        if ((diff>>i)& 1)
        {
            b=parent[b][i];
        }
    }
    //now they are in same level. use binary lifting
    if(a==b)cout<< a<<endl;   //if they are same, it is the LCA
    else{
        for (int i=LOG-1; i>=0; i--)
        {
            if(parent[a][i]!=parent[b][i])
            {
                a=parent[a][i];
                b=parent[b][i];
            }
        }
        cout<<parent[a][0]<<endl;
    }
    
    
    
    
    
    
    
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


