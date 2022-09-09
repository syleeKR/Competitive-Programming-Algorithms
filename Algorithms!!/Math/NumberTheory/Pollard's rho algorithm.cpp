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
typedef __int128 lll;

//Find a divisor that divides n in under than O( sqrt(minP) ) <= O( N^1/4 )
//code works for long long n
long long gcd(long long a, long long b)
{
    if(b==0)return a;
    return gcd(b, a%b);
}
long long f(long long x, long long c, long long mod)
{
    return ((lll)x*x%mod+c)%mod;
}
long long PollardRho(long long n)
{
    /* initialize random seed */
    //srand ((unsigned int)time(NULL));
 
    /* no prime divisor for 1 */
    if (n==1) return n;
 
    /* even number means one of the divisors is 2 */
    if (n % 2 == 0) return 2;
 
    long long x = (rand()%(n-2))+2;
    long long y = x;
    long long c = (rand()%20)+1;
 
    /* Initialize candidate divisor (or result) */
    long long d = 1;
 
    /* until the prime factor isn't obtained.
       If n is prime, return n */
    while (d==1)
    {
        x=f(x,c,n);
        y=f(y,c,n);
        y=f(y,c,n);

        /* check gcd of |x-y| and n */
        d = gcd(abs(x-y),n);
 
        if (d==n)
        {
            x = (rand()%(n-2))+2;
            y = x;
            c = (rand()%20)+1;
            d = 1;
        }
    }
 
    return d;
}


int main()
{
    ll x= mod*mod;
    cout<<x<<endl;
    cout<<PollardRho(x)<<endl;
}
