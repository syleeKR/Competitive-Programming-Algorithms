
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5;
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

//Divide and Conquer Optimization : O(mn^2) -> O(m nlogn)
// Recursion : dp[i][j] = Min[k] ( dp[i-1][k] +C[k][j])
// Condition : (고정된 i에서) j 일때 최소값을 주는 k를 opt(j) 라 할때 optj가 monotonic.
// 각각의 dp[i][1~n]를 O(nlogn)에 calculate.

//만약 k<=j & C[k][j]가 Monge array 라면 optj가 monotonic임을 보일 수 있음.

ll val[8001];
ll sum[8001];
ll dp[801][8001];

long long C(int k, int j)    //C[k][j] 값을 계산
{
    return (j-k)*(sum[j]-sum[k]);
}


void compute(int l, int r, int optl, int optr, int i) //compute dp[i][l] ~ dp[i][r]을 찾는다. 가능한 k는 optl~optr
{
    if(l>r)return;
    
    int mid = (l+r)/2;
    pair<ll, int> best = {LLONG_MAX, -1};     //min을 구하는 것이므로 LLONG_MAX
    
    for (int k = optl; k <=min(mid-1,optr); k++)
    {
        best = min(best, {dp[i-1][k] + C(k, mid), k});
    }

    dp[i][mid] = best.first;
    int opt = best.second;
    
    compute(l, mid - 1, optl, opt,i);
    compute(mid + 1, r, opt, optr,i);
    
}

void solve()
{
    int n,m; cin>>n>>m;
    REP1(i,n)cin>>val[i];
    REP1(i,n)sum[i] = sum[i-1]+val[i];
    
    //initialize;
    REP0(i,m+1)dp[i][0]=0;
    REP0(i,n+1)dp[1][i]=i*sum[i];
    //fill the dp array

    for(int i=2; i<=m; i++)
    {
        for(int j=1; j<i; j++)
        {
            dp[i][j] = sum[j];
        }
        compute(i,n,1, n-1,i); //fill dp[i][1~n]
    }
    
    cout<<dp[m][n]<<endl;
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



