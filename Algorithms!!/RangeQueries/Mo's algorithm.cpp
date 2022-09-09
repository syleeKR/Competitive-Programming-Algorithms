
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
// problem : find out the number of different elements in ar[l,....,r]
/*   Mo's algorithm    Time complexity : O(  (Q+N)sqrt(N)*F   +    QlogQ    )  */


//      query     //
int q;
int sqrtQ;
struct Query
{
    int index, start, end;
};
bool cmp(Query & q1, Query& q2)
{
    if (q1.start/sqrtQ!=q2.start/sqrtQ)return q1.start/sqrtQ<q2.start/sqrtQ;
    return q1.end<q2.end;
}
//                //


int n;
int ar[100000+1];
int exist[1000000+1];       //storing the existence for each number.
int ansforquery[100000];    //storing answers for each query

void solve()
{
    // reading array data and queries
    cin>>n;
    REP1(i,n)cin>>ar[i];
    cin>>q;
    sqrtQ = sqrt(q);
    vector<Query> queries;
    REP0(i,q)
    {
        int s,e; cin>>s>>e;
        queries.pb({i,s,e});
    }
    
    //sort queries for Mo's algorithm.
    sort(queries.begin(), queries.end(),cmp);
    
    //solve first query. initialize left and right.
    int left = queries[0].start; int right = queries[0].end;
    int ans=0;
    for(int pos=left; pos<=right; pos++)
    {
        if(exist[ar[pos]]==0)
        {
            ans++;
        }
        exist[ar[pos]] ++;
    }
    ansforquery[queries[0].index]=ans;
    
    //solve each query in sorted order.
    for(int i=1; i<queries.size(); i++)
    {
        int start=queries[i].start; int end=queries[i].end; int index=queries[i].index;
        
        while(left>start)
        {
            left--;
            
            if(exist[ar[left]]==0)ans++;
            exist[ar[left]]++;
        }
        while(right<end)
        {
            right++;
            
            if(exist[ar[right]]==0)ans++;
            exist[ar[right]]++;
        }
        while(left<start)
        {
            exist[ar[left]]--;
            if(exist[ar[left]]==0)ans--;
            
            left++;
            
        }
        while(right>end)
        {
            exist[ar[right]]--;
            if(exist[ar[right]]==0)ans--;
            
            right--;
            
        }
  
        ansforquery[index]=ans;
    }

    
    //print out the answers
    REP0(i, q)cout<<ansforquery[i]<<endl;
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

