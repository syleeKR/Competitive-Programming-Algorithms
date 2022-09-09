
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

//Slope Trick
//dp[i][x] : 1~i 번째 최소값. bi=x로 놓음.
//dp[i][x] = min[for all k<x](dp[i-1][k]+ |ai-x|)
//Think dp[i][x] as a function f(x)
// We will going to calculate f(x)[store the slope changing points of f & minval] in O(logn). Repeat this for i=1~n. We get O(nlogn) complexity

//min[for all k<x](dp[i-1][k]) 부분은 기울기가 0이하인 부분만을 살리고 x축으로 1평행이동
//|ai-x|는 ai이하 기울기 1감소, ai이상 기울기 1증가

//priority_queue 사용. pq의 원소 x는 x이하 기울기를 1감소 시키라는 것.
// shift : 평행이동 된 정도. ans : max 값 가지고 있음.


void solve()
{
    int n;cin>>n;
    int ar[n+1];
    REP1(i,n)cin>>ar[i];
    
    ll ans=0;
    int shift=0;
    priority_queue<int> pq;
    //initialize
    pq.push(ar[1]);
    // calculate.
    REP(i,2,n)
    {
        shift++;
        int minpos = pq.top() + shift;
        
        if(minpos<=ar[i])
        {
            pq.push(ar[i]-shift);
        }
        else{
            
            pq.push(ar[i]-shift);
            pq.push(ar[i]-shift);
            pq.pop();
            ans+=(minpos -ar[i]);
        }
    }
    
    cout<<ans<<endl;
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


