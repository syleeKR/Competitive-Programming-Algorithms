//
//  Diameter of Tree.cpp
//  Learn C++
//
//  Created by 이서용 on 2021/03/14.
//

#include <bits/stdc++.h>
using namespace std;


//Diameter is the maximum length between two nodes in a tree.

const int MxN = 5;
vector<int> adj[MxN+1]; // adjacency list of tree
int depth[MxN+1];


void dfs(int parent, int child)
{
    // process the node "start" here
    depth[child]=depth[parent]+1;

    //      //
    for (auto x : adj[child])
    {
        if (x!= parent){
        dfs(child, x);
        }
    }
}

//O(n+m) algorithm. simply just two dfs!
int dfs_diameter()
{
    // begin dfs
    memset(depth, 0, sizeof(depth));
    dfs(0,1); // arbitary root 1
    
    
    // Now find out the node with the greatest depth
    int furthest_node=0;
    int max_depth=0;
    
    for (int i=1; i<=MxN; i++)
    {
        if (depth[i]> max_depth)
        {
            max_depth = depth[i];
            furthest_node= i;
        }
    }
    
    // begin another dfs rooted with furthest_node
    memset(depth, 0, sizeof(depth));
    dfs(0, furthest_node);
    
    // the biggest value in depth array is the diameter of the tree.
    int diameter = 0 ;
    for(int i=1; i<=MxN; i++)
    {
        diameter =  max(diameter, depth[i]);
    }
    return diameter;
}







int main()
{
    dfs_diameter();
}
