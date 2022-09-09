
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

//Solution 1.   <just dp : O(n^2)>

long long nCr(int n, int r, int mod)
{
    if(n<r)return 0;
    if(n==0 && r==0)return 1;
    long long dp[n+1][n+1];
    for(int i=1; i<=n; i++){dp[i][0]=1; dp[i][i]=1;}
    for(int i=2; i<=n; i++)
    {
        for(int j=1; j<i; j++)
        {
            dp[i][j]= dp[i-1][j-1]+dp[i-1][j];
            dp[i][j]%=mod;
        }
    }
    return dp[n][r];
}



//Solution 2.    <페르마 소정리로 역원을 찾아서 O(n * log p) 시간에 계산하자.>
long long modpow(int x, int y, int mod)
{
    if (y == 0) return 1;
    long long ans = modpow(x,y/2,mod);
    ans = (ans*ans)%mod;
    if (y%2 == 1) ans = (ans*x)%mod;
    return ans;
}
long long inverse(int x, int mod) {return modpow(x, mod-2, mod);}

long long nCr_Fermat(int n, int r, int mod)   //mod is prime!!
{
  
    if (n < r) return 0;
    if (r == 0)return 1;
     
        // Fill factorial array so that we
        // can find all factorial of r, n
        // and n-r
    long long fac[n + 1]; fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = (fac[i - 1] * i) % mod;
     
    return (fac[n] * inverse((int)fac[r], mod) % mod * inverse((int)fac[n - r], mod) % mod) % mod;
}


//Solution 3.   <Lucas Theorem. 나누는 수가 작을때 사용.O(p^2logp) >
// nCr%p 는 n과 r을 p진법으로 바꾸고 각각의 niCri들의 곱과 같다.

long long nCr_Lucas(int n, int r, int p)
{
    if (r==0) return 1;
    // Compute last digits of n and r in base p
    int ni = n%p, ri = r%p;
     
    return nCr_Lucas(n/p, r/p, p) * nCr(ni, ri, p)% p;
}




int main()
{
    
}

