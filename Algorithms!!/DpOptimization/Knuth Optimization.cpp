
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 5e3;
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
//M_PI, M_E

//Knuth Optimization
//Recurrence : dp[i][j] = min[i<=k<j](dp[i][k]+dp[k+1][j]+C[i][j])
//Condition. #1. C[i][j] is Monge array #2.C[a][d]>=C[b][c] (a<=b<=c<=d)

//Following Property holds. opt[i][j-1]<=opt[i][j]<=opt[i+1][j].
//Using the property, we calculate dp[i][j] in the order of increasing j-i, and we limit the range of k.
//This leads to naive O(n^3) -> O(n^2)


ll dp[MxN+1][MxN+1];
int opt[MxN+1][MxN+1];
int ar[MxN+1];
ll sum[MxN+1];


void solve()
{
    int n; cin>>n;
    REP1(i,n)cin>>ar[i];
    REP1(i,n)sum[i] = sum[i-1]+ar[i];
    
    //Base Case
    for(int i=1; i<=n; i++)
    {
        dp[i][i]=0;
        opt[i][i]=i;
    }
    //1. iterate in increasing length 2. limit the range of k
    
    for(int len =2; len<=n; len++)
    {
        for(int left=1; left<=n-len+1; left++)
        {
            int right = left+len-1;
            
            dp[left][right]=LLONG_MAX;
            for(int k=max(opt[left][right-1],left); k<=min(opt[left+1][right],right-1); k++)
            {
                if(dp[left][right] > dp[left][k]+dp[k+1][right]+sum[right]-sum[left-1])
                {
                    dp[left][right] = dp[left][k]+dp[k+1][right]+sum[right]-sum[left-1];
                    opt[left][right] = k;
                }
            }
            
        }
    }
    
    cout<<dp[1][n]<<endl;
    
    
    reset(dp);
    reset(opt);
    reset(ar);
    reset(sum);
}





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


