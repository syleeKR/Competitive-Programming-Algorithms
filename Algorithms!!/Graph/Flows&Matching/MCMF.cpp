#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 805;
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
//O(VE *F) Minimum cost Maximum Flow. O(VE) for SPFA(same limit as bellman ford)

int residual[MxN][MxN];
vint adj[MxN];
int cost[MxN][MxN];

int dist[MxN];
int parent[MxN];
bool inQ[MxN];


bool SPFA(int n, int m, int source, int sink)
{
    REP1(i,n+m+2)
    {
        parent[i]=-1;
        dist[i]=inf;
        inQ[i]=false;
    }
    dist[source]=0;
    parent[source]=0;
    queue<int> q;
    q.push(source);
    inQ[source]=true;
    
    while(!q.empty())
    {
        int curr = q.front(); q.pop(); inQ[curr]=false;
        for (auto next : adj[curr])
        {
            if (residual[curr][next]>0 && dist[next]>dist[curr]+cost[curr][next])   //if there is path(in adj& residual>0) and distance can be updated
            {
                dist[next]=dist[curr]+cost[curr][next];     //update dist
                parent[next]=curr;                          //update parent
                
                if(!inQ[next])    //if next is not in Q we add it.
                {
                    q.push(next);
                    inQ[next]=true;
                }
            }
        }
    }
    return (parent[sink]!=-1);   //경로가 있는지 없는지 return
}

pii MCMF(int n, int m, int source, int sink)
{
    int maxflow=0;
    int mincost=0;

    while(SPFA(n,m, source, sink))   //there exits path that can flow
    {
        //calculate flowofpath
        int flowofpath=INT_MAX;
        int curr = sink;
        while(curr!=source)
        {
            flowofpath = min(flowofpath, residual[parent[curr]][curr]);
            curr = parent[curr];
        }
        //update residual graph, maxflow, mincost
        curr=sink;
        while(curr!=source)
        {
            mincost += cost[parent[curr]][curr]*flowofpath;
            residual[parent[curr]][curr] -= flowofpath;
            residual[curr][parent[curr]] += flowofpath;
            curr = parent[curr];
        }
        //update maxflow
        maxflow += flowofpath;
    }
    return {mincost, maxflow};   //pair of mincost, maxflow
}

void solve()
{
    //initialize adj, and residual graph.
    int n,m; cin>>n>>m;
    
    int source = n+m+1; int sink = n+m+2;
    REP1(i,n+m+2)REP1(j,n+m+2)residual[i][j]=0;
    
    
    REP1(i,n)
    {
        int num; cin>>num;
        while(num--){
            int v; cin>>v;
            adj[i].pb(v+n);
            adj[v+n].pb(i);
            residual[i][v+n]++;
            int w; cin>>w;
            cost[i][v+n] =w;
            cost[v+n][i]=-w;
        }
    }
    REP1(i,n)
    {
        adj[source].pb(i);
        adj[i].pb(source);
        residual[source][i]=1;
        cost[source][i]=0;
        cost[i][source]=0;
    }
    REP(i, n+1, n+m)
    {
        adj[i].pb(sink);
        adj[sink].pb(i);
        residual[i][sink]=1;
        cost[i][sink]=0;
        cost[sink][i]=0;
    }
    
    pii mcmf = MCMF(n,m, source, sink);
    cout<<mcmf.se<<endl<<mcmf.fi<<endl;
    
    
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


