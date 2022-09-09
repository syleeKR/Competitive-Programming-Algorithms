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
//Dinic's algorithm : O(min(EV^2), min(EF))  : a improved version of ford-fulkerson & Edmonds Karp

int residual[MxN][MxN];
vint adj[MxN];

int level[MxN];
int savepoint[MxN];

const int source = 1;
const int sink = 2;


bool bfs(int n)        //flow 더 보내기 가능?
{
    REP1(i,n)level[i]=-1;
    level[source]=0;

    queue<int> q;
    q.push(source);
    
    while(!q.empty())
    {
        int curr = q.front(); q.pop();
        for (auto next : adj[curr])
        {
            if (residual[curr][next]>0 && level[next]==-1)
            {
                level[next]=level[curr]+1;
                q.push(next);
            }
        }
    }
    return (level[sink]!=-1); // is it possible to reach the sink??
}

int dfs(int curr, int destination, int flow)   //curr -> destination 까지 flow를 넘기는 하나의 path 찾기. 그 과정에서 residual update
{
    if(curr==destination)return flow;
    
    for (int &i= savepoint[curr]; i<adj[curr].size(); i++)    //look for all adjacent edges
    {
        int next = adj[curr][i];
        if(level[next]==level[curr]+1 && residual[curr][next]>0)   //level이 1증가하고 이동가능(residual>0) 하면. 즉 level graph상에서 edge가 있으면 가본다.
        {
            int possibleflow = dfs(next, destination, min(flow, residual[curr][next]));
            
            if(possibleflow>0)    //경로를 찾았다!!!!!!!
            {
                residual[curr][next] -= possibleflow;     //residual graph update
                residual[next][curr] += possibleflow;
                return possibleflow;     //한번 dfs(source, sink)부를때마다 하나의 path를 따라서 flow를 보낸다. 이과정을 하나의 level graph에 대해 불가능할때까지 반복.
            }
        }
    }
    return 0;  //no possible flow from source to sink in current level graph.
}

int Dinic(int n)
{
    int maxflow=0;

    while(bfs(n))   //there exits path that can flow
    {
        reset(savepoint);   //we are going to continuously work on a single level graph, so we need to store the edges that we have traveled before.
        
        while(true)      //for a single level graph
        {
            int flow = dfs(source, sink, inf);
            maxflow += flow;
            if(flow==0)break;
        }
    }
    return maxflow;
}

void solve()
{
    //initialize adj, and residual graph.
    int n,m; cin>>n>>m;
    
    REP1(i,n)REP1(j,n)residual[i][j]=0;
    
    REP0(i,m)
    {
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);  //even if it is directed graph!!!
        residual[u][v]++;
    }
    
    cout<<Dinic(n)<<endl;
    
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


