
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int MxN = 1e5+10;
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

const int LOG = 18;
int SparseTable[MxN][LOG];   //SparseTable[i][j] : min(i~i+2^j-1)
int max2exponent[MxN];


int query(int l, int r)   //O(1) per RMQ!!!
{
    int lenofInterval = r-l+1;
    int exponent = max2exponent[lenofInterval];
    return min(SparseTable[l][exponent], SparseTable[r-(1<<exponent)+1][exponent]);
}


void solve()
{
    int n,m; cin>>n>>m;
    
    /* preprocessing
     1.SparseTable
     2.max2exponent[i]:returns the largest j where (1<<j)<=i
     O(nlogn)
     */
    
    //building the SparseTable : O(nlogn)
    REP0(i,n)
    {
        cin>>SparseTable[i][0];
    }
    for(int k=1; k<LOG; k++)
    {
        for(int i=0; i<=n-(1<<k); i++)
        {
            SparseTable[i][k]= min(SparseTable[i][k-1], SparseTable[i+(1<<(k-1))][k-1]);
        }
    }
    
    //build max2exponent : O(n)
    max2exponent[1]=0;
    int exponent =1; int val = 2;
    for(int i=2; i<=n; i++)
    {
        if (i==val*2)
        {
            exponent++;
            val*=2;
        }
        max2exponent[i] = exponent;
    }
    
    
    
    //m queries
    while(m--)
    {
        int l,r; cin>>l>>r;
        cout<<query(l-1, r-1)<<endl;
    }
    
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

