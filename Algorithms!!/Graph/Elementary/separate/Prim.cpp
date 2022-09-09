//
//  Prim.cpp
//  Learn C++
//
//  Created by 이서용 on 2021/03/14.
//

#include <bits/stdc++.h>
using namespace std;
const int MxN = 10;

vector<pair<int, int>> adj[MxN];



// O(mlogm +n) algorithm for finding MST

void Prim(int start_node)
{
    priority_queue<pair<int, int>> pq;
    bool included[MxN+1];
    for (int i=1; i<=MxN; i++) included[i]=false;
    
    pq.push({0,start_node});
    included[start_node]=true;
    
    
    while(!pq.empty())
    {
        int node=pq.top().second; pq.pop();
        if (included[node]) continue;
        included[node]=true;
        
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
    Prim(1);
}
