
#include <bits/stdc++.h>
using namespace std;
int inf = INT_MAX;




const int N=5;
vector<tuple<int, int,int>> edge_list;   //edge list
int dist[N+1];




// can be applied when it has no negative cycle.
// Algorithm detects negative cycle. If nth round decreases a distance, this means the existence of negative cycle.
//O(nm)
void Bellman_Ford(int x)
{
    for(int i=0; i<=N; i++) dist[i]=inf;      // set the initial distance to inf
    dist[x]=0;                                // set starting node dist to 0
    
    for(int i=1; i<=N-1; i++)    // iterate through n(number of nodes) times
    {
        for (auto edge : edge_list)   //iterate through m(number of edge) times
        {
            int a,b,w; tie(a,b,w) = edge;
            
            dist[b] = min(dist[b], dist[a] + w);
        }
        
        
    }
    
    
}







int main()
{
    
    Bellman_Ford(1);
}

