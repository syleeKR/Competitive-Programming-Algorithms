
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5+1;
const int MxK = 1e9;
const int inf = INT_MAX;
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


const int MaxNode = 5*1e6+1;
struct Trie
{
    int trie[MaxNode][26];
    int count[MaxNode];
    int nextnode=1;
    
    void init()
    {
        memset(trie, -1, sizeof(trie));
        memset(count, 0, sizeof(count));
    }
    
    bool exist(string & s)
    {
        int node=0;
        for(int i=0; i<(int)s.size(); i++)
        {
            if(trie[node][(int)s[i]-int('a')]==-1)return false;
            else node =trie[node][(int)s[i]-int('a')];
        }
        if(count[node]>0)return true;
        else return false;
    }
    
    void add(string &s)
    {
        int node=0;
        for(int i=0; i<(int)s.size(); i++)
        {
            if(trie[node][(int)s[i]-int('a')]==-1)
            {
                trie[node][(int)s[i]-int('a')]=nextnode;
                node=nextnode;
                nextnode++;
            }
            else
            {
                node =trie[node][(int)s[i]-int('a')];
            }
        }
        count[node]++;
    }
    
};




int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t; cin>>t;  //t=1;
    while(t--)
    {
        solve();
    }
}

