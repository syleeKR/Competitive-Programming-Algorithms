
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

//find palindrome in O(n)

string manipulate(string s)
{
    string changed="#";
    for(int i=0; i<(int)s.size(); i++)
    {
        changed+=s[i];
        changed+="#";
    }
    return changed;
}
vector<int> Manacher(string s)    //returns longest palindrome substring lps array.
{
    vector<int> lps((int)s.size());  //original string size:N -> manipulated string size:2N+1;
    int r=0; int c=0;   // [2*c-r ,r] is palindrome and r is the maximum untill now
    
    for(int i=0; i<(int)s.size(); i++)
    {
        if(i<=r)lps[i] = min(r-i, lps[2*c-i]);
        else lps[i]=0;
        
        while( (i-lps[i]-1)>=0  &&  (i+lps[i]+1)<s.size()  &&  s[i+lps[i]+1]==s[i-lps[i]-1] )lps[i]++;
        
        
        if(r<lps[i]+i)
        {
            r=lps[i]+i;
            c=i;
        }
    }
    
    return lps;
}






void solve()
{
    vint v= Manacher(manipulate("aaaaa"));
    REP0(i,v.size())cout<<v[i]<<endl;
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

