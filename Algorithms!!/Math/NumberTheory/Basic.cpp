
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

/*
 -density of primes : O(N/lnN)
 -goldbach's conjecture : even number = sum of two primes
 -twin prime conjecture : p,p+2 prime
 -legendre's conjecture : prime exists between n^2, (n+1)^2
 */


//primality test  : O(sqrtN)
bool prime(int n)
{
    if (n < 2) return false;
    for (int x = 2; x*x <= n; x++)if (n%x == 0) return false;
    return true;
}

//prime factorisation : O(sqrtN)
vector<int> factors(int n)
{
    vector<int> f;
    for (int x = 2; x*x <= n; x++)
    {
        while (n%x == 0)
        {
            f.push_back(x);
            n /= x;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}

//Sieve of erastosthenes : O(NloglogN)
int sieve[MxN];
void build_sieve(int n){
    reset(sieve);
    for (int x = 2; x <= n; x++)
    {
        if (sieve[x]) continue;    //not prime;
        for (int u = 2*x; u <= n; u += x) sieve[u] = x;
    }
}

//Euclid's algorithm(finding gcd) : O( log(min(a,b)) )

int gcd(int a, int b)
{
    if(b==0)return a;
    return gcd(b, a%b);
}

int lcm(int a, int b)
{
    return a*b/gcd(a,b);
}


//Euler's totient function : 1~n 의 숫자중 n과 서로소(coprime=gcd가 1)인 숫자 개수. 소수 <-> phi(n)=n-1. gcd(a,b)=1 -> phi(ab)=phi(a)phi(b)
//Euler product theorem : phi(n) = nPi[1-1/pi] = Pi[pi^(ai-1)*(pi-1) ]
//O(sqrtN)
int phi(int n)
{
    int ans=1;
    for (int x = 2; x*x <= n; x++)
    {
        int count=0;
        while (n%x == 0)
        {
            n /= x;
            count++;
        }
        if(count>0) ans *= pow(x, count-1)*(x-1);
    }
    if (n > 1) ans *= (n-1);
    return ans;
}


//modular exponentiation (x^y) : O(log y)
int modpow(int x, int y, int mod)
{
    if (y == 0) return 1;
    long long ans = modpow(x,y/2,mod);
    ans = (ans*ans)%mod;
    if (y%2 == 1) ans = (ans*x)%mod;
    return ans;
}


//Fermat's theorem : if p: prime, (x,p)=1, then  x^(p-1) %p =1
//Euler's theorem :  if (x,m)=1,  x^(phi(m)) % m =1
//wilson's theorem : p is prime <-> (p-1)! %p = p-1


//modular inverse : if (x,m)=1,  inverse of x modulo m = x^(phi(m)-1)
//O(sqrt mod)
int inverse(int x, int mod)
{
    if(gcd(x,mod)!=1)return 0; //doesn't exist.
    return modpow(x, phi(mod)-1, mod);
    // return modpow(x, mod-2, mod) if mod is prime.
}



//Diophantine equations. We can use this to get modulo inverse in log(n)
//Extended euclidean algorithm : solve ax+by = gcd(a,b);
//O(log(min(a,b)))
pii Extended(int a, int b)
{
    if (a == 0) return {0,1};
    
    int x,y;
    pii p = Extended(b%a, a);
    x=p.first; y=p.second;
 
    return {y - (b/a) * x, x};
}
pii Diophantine(int a, int b, int c)
{
    if(c%gcd(a,b)!=0)return {0,0}; //impossible!!!. to be solvable, c should divide gcd(a,b)
    else{
        int mult = c/gcd(a,b);
        pii p = Extended(a,b);
        return {p.first*mult, p.second*mult};
    }
}
//find modular inverse in O(log mod)
int inverse_Euclidean(int x, int mod)
{
    return Extended(x, mod).fi;
}


//Chinese remainder theorem : O(NlogM) if we use extended euclidean algorithm for calculating inverse, O(NsqrtM) if we use phi function for inverse.
// find x st. a1(mod m1) & a2(mod m2) &.....& an(mod mn).  mi's are coprime

int Chinese(vector<int> modular, vector<int> remainder)
{
    // Compute product of all numbers
    int total_product = 1;
    int n = (int)modular.size();

    for (int i = 0; i < n; i++)
        total_product *= modular[i];
 
    // Initialize result
    int result = 0;
 
    // Apply formula
    for (int i = 0; i < n; i++) {
        int pp = total_product / modular[i];
        result += remainder[i] * Extended(pp, modular[i]).fi * pp;
        result %= total_product;
    }
 
    return result % total_product;   //result + total_product*k 꼴은 모두 해임
}
 
 



//Lagrange's theorem:positive int = sum of four squares
//Zeckendorf's theorem :positive int : unique sum of Fibonacci where no numbers are same and no numbers are consecutive Fibonacci
//Pythagorean triple : 0<m<n, (n,m)=1, n or m is even : (n^2-m^2, 2nm, n^2+m^2) produces all pythagorean triple.




int main()
{
    cout<<prime(12)<<endl;
    vint f = factors(12);
    REP0(i, f.size())cout<<f[i]<<endl;
    cout<<gcd(12, 36)<<" "<<lcm(4,6)<<endl;
    cout<<phi(7)<<" "<<phi(12)<<endl;
    cout<<modpow(2,5,10)<<endl;
    cout<<inverse(3,17)<<endl;
    cout<<Extended(3,4).fi<<" "<<Extended(3,4).se<<endl;
    cout<<Extended(5,0).fi<<" "<<Extended(5,0).se<<endl;
    cout<<Diophantine(3,4,7).fi<<" "<<Diophantine(3,4,7).se<<endl;
    


}

