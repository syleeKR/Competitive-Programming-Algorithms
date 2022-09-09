/*
 <Maxflow Mincut Theorem>
 
 Max-flow = Min-cut
 */




#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5;
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


int residual[MxN][MxN];
vint adj[MxN];


void dfs_findcut(int curr, bool canvisit[])
{
    canvisit[curr]=true;
    for(auto next : adj[curr])
    {
        if (residual[curr][next]>0 && canvisit[next]==false)
        {
            dfs_findcut(next, canvisit);
        }
    }
}



vector<pii> MinCut(int n, int source)
{
    vector<pii> cuts;
    
    bool canvisit[n+1];
    reset(canvisit);
    
    dfs_findcut(source, canvisit);
    
    REP1(startvertex,n){
        for (auto endvertex : adj[startvertex])
        {
            if (canvisit[startvertex]&& !canvisit[endvertex]) cuts.pb({startvertex, endvertex});
        }
    }
    return cuts;
}


