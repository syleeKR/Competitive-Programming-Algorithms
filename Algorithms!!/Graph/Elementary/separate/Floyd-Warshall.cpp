//
//  Floyd-Warshall.cpp
//  Learn C++
//
//  Created by 이서용 on 2021/03/06.
//

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll inf = INT_MAX;


// Find all shortest paths!!
// O(V^3) algorithm.
const int MxN = 5;
ll adj[MxN+1][MxN+1];   //Use adjacency matrix
ll dist[MxN+1][MxN+1];   //store the minimum distances


void Floyd_Warshall()
{
    // first, we initialize the distance matrix
    for (int i=1; i<=MxN; i++)
    {
        for (int j=1; j<=MxN; j++)
        {
            dist[i][j] = inf;
            if (i==j) dist[i][j] = 0;
            else if (adj[i][j]!=0) dist[i][j] = adj[i][j];
        }
    }
    
    // Now we calculate the minimum distances
    
    for (int bridge=1; bridge<=MxN; bridge++)   // for selecting who will be the bridge??   start->bridge-> end
    {
        for (int start=1; start<=MxN; start++)
        {
            for (int end=1; end<=MxN; end++)
            {
                dist[start][end] = min (dist[start][endl],  dist[start][bridge]+dist[bridge][end])
            }
        }
    }
}





int main()
{
    Floyd_Warshall();
}
