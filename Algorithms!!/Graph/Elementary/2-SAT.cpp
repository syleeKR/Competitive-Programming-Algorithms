
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 2e4;
const int MxK = 1e9;
const int inf = INT_MAX;
#define REP0(i,n) for(int i=0; i<n; i++)
#define REP1(i,n) for(int i=1; i<=n; i++)
#define REP(i,a,b) for(int i=a; i<=b; i++)
#define all(x) x.begin(), x.end()
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
//M_PI, M_E

vint adj[MxN+1];
vint rev[MxN+1];
vint component[MxN+1];
vint family[MxN+1];
vint topology;
int value[MxN+1];
bool visited[MxN+1];
int parent[MxN+1];
int n,m;

int NOT(int x){return (x>n)?(x-n):(x+n);}



void dfs_visit(int curr)
{
    visited[curr]=true;
    for(auto next :adj[curr])if(visited[next]==false)dfs_visit(next);
    topology.pb(curr);
}
void dfs_rev(int curr, int p)
{
    family[p].pb(curr);
    visited[curr]=true;
    parent[curr]=p;
    for(auto next : rev[curr])if(visited[next]==false)dfs_rev(next,p);
}
void build_scc()
{
    REP1(i,2*n)
    {
        if(visited[i]==false)dfs_visit(i);
    }
    reverse(all(topology));
    reset(visited);
    for(auto i : topology)
    {
        if(visited[i]==false)dfs_rev(i,i);
    }
    
}

void dfs_comp(int curr)
{
    visited[curr]=true;
    
    for(auto next : component[curr])
    {
        if(visited[next]==false)dfs_comp(next);
    }
    
    
    topology.pb(curr);
    
}

void sort_component()
{
    topology.clear();
    reset(visited);
    REP1(i, 2*n)
    {
        if(parent[i]==i && visited[i]==false)
        {
            dfs_comp(i);
        }
    }
    reverse(all(topology));
}


void solve()
{
    cin>>n>>m;
    while(m--)
    {
        int a,b; cin>>a>>b;
        if(a<0)a = NOT(-a);
        if(b<0)b= NOT(-b);
        adj[NOT(a)].pb(b);
        adj[NOT(b)].pb(a);
        rev[b].pb(NOT(a));
        rev[a].pb(NOT(b));
    }
    
    build_scc();
    for(int i=1; i<=2*n; i++)
    {
        for(auto x: adj[i])
        {
            if(parent[i]!=parent[x])
            {
                component[parent[i]].pb(parent[x]);
            }
        }
    }
    sort_component();
    reverse(all(topology));
    memset(value, -1, sizeof(value));
    
    REP0(i,topology.size())
    {
        for(auto x : family[topology[i]])
        {
            if(value[x]!=-1)continue;
            if(value[NOT(x)]!=-1)
            {
                value[x] = (value[NOT(x)]^1);
                continue;
            }
            value[x] =1;
            for(auto next : adj[x])
            {
                if(value[next]==0)value[x]=0;
            }
            
        }
    }
    
    
    bool pos=true;
    REP1(i,n)
    {
        if(parent[i] == parent[NOT(i)])pos=false;
    }
    
    cout<<pos<<endl;
    if(pos)REP1(i,n)cout<<value[i]<<" ";
    
    
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



