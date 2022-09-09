
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
//M_PI, M_E

//The number of objects are equal to the average number of symmetrical pictures(taken over all symmetries)
//The number of orbits are equal to the average number of fixed points int the group action(taken over all the group elements)

int gcd(int a, int b)
{
    if(b==0)return a;
    return gcd(b, a%b);
}
long long pow(int a, int b)
{
    if(b==0)return 1;
    ll ans = pow(a,b/2);
    ans = ans*ans;
    if(b%2==1)ans *= a;
    return ans;
}

long long calc(int n, int k)
{
    ll ans=0;
    
    for(int symmetry=1; symmetry<=n; symmetry++)   //대칭 없이 회전 : n개의 symmetry
    {
        ans+= pow(k, gcd(n, symmetry));
    }
    if(n%2==1){
        for(int symmetry=0; symmetry<n; symmetry++)    //대칭 : n개의 symmetry
        {
            ans+=pow(k, ceil(n/2.0));
        }
    }
    else
    {
        for(int symmetry=0; symmetry<n; symmetry++)    //대칭 : n개의 symmetry
        {
            if(symmetry%2==0)ans+=pow(k, n/2+1); //대칭축이 꼭지점을 뚫고 지나가는 경우
            else ans+=pow(k, n/2);               //대칭축이 두 꼭지점 사이에 있는 경우
        }
    }
    
    return ans/2/n;
}





int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    
    int numcolor; int length_of_necklace;
    cin>>numcolor>>length_of_necklace;
    while(length_of_necklace>0)
    {
        cout<<calc(length_of_necklace, numcolor)<<endl;
        cin>>numcolor>>length_of_necklace;
    }

}

