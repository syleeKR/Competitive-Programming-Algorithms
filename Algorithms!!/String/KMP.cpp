
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
//vector<int> adj[MxN+1];
//ll dp[MxN];



//given a text and a pattern we want to print out all the occurences!
// Time complexity O(n) in the worst case (preprocessing -failure ftn takes O(m) time)

vector<int> failure_ftn(const string& pat)
{
    int m  = (int)pat.size();
    vector<int> f(m, 0);
    
    int begin=1; int j=0;
    
    while(begin+j<m)
    {
        if (pat[begin+j]==pat[j])
        {
            j++;
            f[begin+j-1]=j;
        }
        else{
            if (j==0)
            {
                begin++;
            }
            else{
                begin += j-f[j-1];
                j=f[j-1];
            }
        }
    }
    return f;
}




vector<int> KMP(const string& text, const string& pat)
{
    int n = (int)text.size();
    int m = (int)pat.size();
    vector<int> f = failure_ftn(pat);   //prerpocessed vector
    vector<int> find;   //where we will store the starting positions
    
    int begin=0; int j=0;   //begin indicates the starting position of text, j indicates the position of pat
    
    while(begin <= n-m)    // length condition should be satisfied
    {
        if (j<m && text[begin+j]==pat[j]){
            j++;  // move on to the next character
            if (j==m)find.push_back(begin);    //found the matching position!
        }
        else{      //mismatched
            
            if(j==0) begin++;
            else{
                begin = begin+j-f[j-1];
                j=f[j-1];
            }
        }
    }
    
    return find;
}



void solve()
{
    string text, pat; cin>>text>>pat;
    
    vint v;
    v = KMP(text, pat);
    
    REP0(i,v.size()) cout<< v[i]<<" ";     //zero based indexing
}





int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t; t=1;
    while(t--)
    {
        solve();
    }
}

