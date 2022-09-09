
#include <bits/stdc++.h>
using namespace std;
int inf = INT_MAX;




const int MxN=5;
vector<pair<int,int>> adj[MxN+1];
int dist[MxN+1];
bool processed[MxN+1];    //initially false.




// can be applied when it has no negative edge.

//O(n + mlnm)
void Dijkstra(int x)
{
    for(int i=0; i<=MxN; i++) dist[i]=inf;      // set the initial distance to inf
    dist[x]=0;                                // set starting node dist to 0
    priority_queue<pair<int, int>> pq;
    pq.push({0,x});
    
    
    while(!pq.empty())
    {
        int node=pq.top().second; pq.pop();
        if (processed[node]) continue;
        processed[node]=true;
        
        for (auto u : adj[node])
        {
            int next = u.first; int weight = u.second;
            
            if (dist[next]>dist[node]+weight)
            {
                dist[next]=dist[node]+weight;
                pq.push({-dist[next],next});
            }
        }
    }
    
    
}







int main()
{
    
    Dijkstra(1);
}


