//
//  DFS.cpp
//  Learn C++
//
//  Created by 이서용 on 2021/03/06.
//

#include <bits/stdc++.h>
using namespace std;




const int MxN=5+1;
vector<int> adj[MxN];
bool visited[MxN];




//O(n+m)
void dfs(int node)
{
    if (visited[node]) return;
    visited[node]=true;
    
    //process the node here//
    
    for (auto next :  adj[node])
    {
        dfs(next);
    }
}







int main()
{
    dfs(1);
}
