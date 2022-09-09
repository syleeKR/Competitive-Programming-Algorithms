

#include <bits/stdc++.h>
using namespace std;




const int MxN=5+1;
vector<int> adj[MxN];
bool visited[MxN];
int distance[MxN];
queue<int> q;




//O(n+m)
void bfs(int start)
{
    visited[start]=true;
    q.push(start);
    distance[start]=0;
    
    while (!q.empty())
    {
        int node = q.front(); q.pop();
        
        // process node// only not visited nodes will be added to the queue
        
        for (auto next : adj[node])
        {
            if (visited[next]) continue;
            
            q.push(next);
            distance[next]=distance[node]+1;
            visited[next]=true;
            
        }
        
    }
}







int main()
{
    bfs(1);
}

