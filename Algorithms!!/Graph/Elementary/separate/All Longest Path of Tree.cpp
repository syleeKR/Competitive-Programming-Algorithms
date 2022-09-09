//
//  All Longest Path of Tree.cpp
//  Learn C++
//
//  Created by 이서용 on 2021/03/14.
//

#include <bits/stdc++.h>
using namespace std;



const int MxN = 10;
vector<int> adj[MxN+1];  // adjacency list.
int maxlength[MxN+1];   //store the maximum length from each node.

int max_len_down[MxN+1];
pair<int, int> max_len[MxN+1][2];    // {value, nextnode}




void dfs_for_down(int parent , int child)
{
    int maxval = -1;
    for (auto x : adj[child])
    {
        if (x!=parent)
        {
            dfs(child, x);
            maxval = max(maxval, max_len_down[x]);
        }
    }
    max_len_down[child] = maxval +1;
}



void dfs_for_up(int parent, int child)
{
    
    
    for (auto x :  adj[child])
    {
        if (x!=parent)
        {
            dfs (child, x);
        }
    }
}




void longest_path()
{
    // calculate maximum path that follows child
    dfs_for_down(0,1);
    
    // calculate maximum path that follows parent
    max_len_up[1][0] = {0,1};
    max_len_up[1][1] = {0,1};
    for (auto x : adj[1])
    {
        if (max_len_down[x] > max_len_up[1][0])
        {
            max_len_up[1][0] = {}
        }
    }
    dfs_for_up(0,1);
    
    
}







int main()
{

    longest_path();
}
