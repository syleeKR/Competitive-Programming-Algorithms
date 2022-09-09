
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


//Convex Hull Optimization
//조건 : 점화식의 형태가 dp[i] = f(i) + min[j<i]( c(j) + m(j) * x(i))
// m(i) 와 x(i)가 sorted 되어 있다면 O(n). 그렇지 못하다면 O(nlogn)



//dp[i] = min(b[j]*a[i] + dp[j]) 를 풀어보자.

struct line {
    long long slope, yintersect;
    long long eval(long long x) { return slope * x + yintersect; }
    long double intersectX(line l) { return (long double) (yintersect - l.yintersect) / (l.slope - slope); }  //평행한 입력 존재하면 따로 처리 필요.
};


ll a[MxN+1], b[MxN+1]; int n;   // a: strictly increasing, b:strictly decreasing
ll dp[MxN+1];      //dp[i]. dp[n]이 답
deque<line> hull;     //convex hull 을 가지고 있음. 감소하는 기울기 순으로 가지고 있음.


ll query(ll x)
{
    while(hull.size()>1 && hull[0].eval(x)>=hull[1].eval(x))
    {
        hull.pop_front();
    }
    return hull[0].eval(x);
}
void insert_line(line l)
{
    while(hull.size()>1 && hull[hull.size()-1].intersectX(l)<=hull[hull.size()-2].intersectX(l))
    {
        hull.pop_back();
    }
    hull.pb(l);
}

void solve()
{
    cin>>n;
    REP1(i,n)cin>>a[i];
    REP1(i,n)cin>>b[i];
    
    //initialize
    dp[1]=0;
    hull.pb({b[1],0});
    
    // calculate dp[i]s using convex hull trick in O(n)
    
    for(int i=2; i<=n; i++)
    {
        dp[i] = query(a[i]);   //a[i]*b[j]+dp[j] 의 최솟값을 찾아서 dp[i]에 저장
        insert_line({b[i], dp[i]});
    }

    
    cout<<dp[n]<<endl;
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


