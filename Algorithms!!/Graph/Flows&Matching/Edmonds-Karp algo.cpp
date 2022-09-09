#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 410;
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
//Edmonds Karp algorithm : O(min(E^2 V), min(EF))  : a improved version of ford-fulkerson

int residual[MxN][MxN];
vint adj[MxN];

bool visited[MxN];
int parent[MxN];


bool bfs(int source, int sink)
{
    reset(visited);
    visited[source]=true;
    parent[source]=0;
    queue<int> q;
    q.push(source);
    
    while(!q.empty())
    {
        int curr = q.front(); q.pop();
        for (auto next : adj[curr])
        {
            if (residual[curr][next]>0 && visited[next]==false)
            {
                visited[next]=true;
                parent[next]=curr;
                q.push(next);
                if(next==sink) return true;    //possible to reach sink;
            }
        }
    }
    return false; //no path to reach sink
}

int Edmonds_Karp(int source, int sink)
{
    int maxflow=0;

    while(bfs(source, sink))   //there exits path that can flow
    {
        //calculate flowofpath
        int flowofpath=INT_MAX;
        int curr = sink;
        while(curr!=source)
        {
            flowofpath = min(flowofpath, residual[parent[curr]][curr]);
            curr = parent[curr];
        }
        //update residual graph
        curr=sink;
        while(curr!=source)
        {
            residual[parent[curr]][curr] -= flowofpath;
            residual[curr][parent[curr]] += flowofpath;
            curr = parent[curr];
        }
        //update maxflow
        maxflow += flowofpath;
    }
    return maxflow;
}

void solve()
{
    //initialize adj, and residual graph.
    int n,m; cin>>n>>m;
    
    int source=1; int sink=2;
    reset(residual);
    
    REP0(i,m)
    {
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);  //even if it is directed graph!!!
        residual[u][v]++;
    }
    
    cout<<Edmonds_Karp(source, sink)<<endl;
    
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

