//
//  Kruskal.cpp
//  Learn C++
//
//  Created by 이서용 on 2021/03/14.
//

#include <bits/stdc++.h>
using namespace std;


const int MxN = 10;
vector<tuple<int,int, int>> edges;   // weight, node, node. edge list rep


// We will use Union - Find structure, which provides union and find in logN time

int link[MxN+1];
for (int i=1; i<=MxN; i++) link[i]=i;
int size[MxN+1];
for (int i=1; i<=MxN; i++) size[i]=1;

int find(int x)     // returns the representative element :  O(log n)
{
    while (link[x]!=x) x = link[x];
    return x;
}
bool same(int a, int b)
{
    return find(a)==find(b);
}
void unite(int a, int b)
{
    a = find(a); b= find(b);
    if (size[a]<size[b]) swap(a,b); // a is always bigger
    link[b] = a;
    size[a] +=size[b];
}








// O(mlogm + nlogm) for finding the MST
// We use edge list representation
void Kruskal()
{
    sort(adj.begin(), adj.end());    // first sort in weight - increasing - order
    
    for (int i =0; i<edges.size(); i++)
    {
        int a,b,w;
        tie(w,a,b) = edges[i]
        if (!same(a,b))
        {
            unite(a,b);
            // process the edge of MST
            // ex) cout<<a<<" "<<b<<endl;
        }
    }
}





int main()
{
    Kruskal();
}
