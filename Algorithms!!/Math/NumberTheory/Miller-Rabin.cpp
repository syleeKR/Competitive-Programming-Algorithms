
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


//O(numrep * (logn)^3 ).
//n 이 long long 범위일때까지 고려함 ->unsigned long long 써야함
typedef __int128 lll;
ll modpow(int x, ll y, ll mod)
{
    if (y == 0) return 1;
    lll ans = modpow(x,y/2,mod);
    ans = (ans*ans)%mod;
    if (y%2 == 1) ans = (ans*x)%mod;
    return ans;
}

bool miillerTest(ll d, ll n, int a)
{
    // Compute a^d % n
    lll x = modpow(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
     return false;
}

bool Miller_Rabin(ll n, int numrep)
{
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
     
    ll d = n - 1;
    while (d % 2 == 0)d /= 2;
     
    // 하나라도 false가 뜨면 바로 합성수. 합성수들을 걸러내는 작업으로 보면됨.
    int a[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};    //n 이 작은 longlong 일때 결정적으로 판별함.
    for (int i = 0; i < numrep; i++)
    {
        if(n==a[i])return true;
        if (!miillerTest(d, n,a[i]))return false;
    }
    return true;
}





int main()
{
    for(int i=1; i<100; i++)
    {
        if(Miller_Rabin(i,12))cout<<i<<endl;
    }
}

