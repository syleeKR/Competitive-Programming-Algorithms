//Seg tree

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//   sum(l,....,r-1)  --> sum(l,r)
struct segtree
{
    int size;
    vector<ll> sums;
    
    void init(int n)
    {
        size=1;
        while (size<n)
        {
            size*=2;
        }
        sums.assign(size*2,0LL);
    }
    
    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx-lx==1)
        {
            if (lx<(int)a.size())
            {
                sums[x] = a[lx];
            }
            return;
        }
        
        
        int m = (lx+rx)/2;
        build(a,2*x+1, lx,m);
        build(a,2*x+2, m, rx);
        sums[x] = sums[2*x+1]+sums[2*x+2];
    }
    
    void build(vector<int> &a)
    {
        build(a, 0,0,size);
    }
    
    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx-lx==1){    //leaf node
            sums[x]=v;
            return;
        }
        int m = (lx+rx)/2;
        if(i<m)
        {
            set(i,v, 2*x+1, lx,m);
        }
        else{
            set(i,v,2*x+2, m, rx);
        }
        sums[x] = sums[2*x+1]+sums[2*x+2];
    }
    
    
    void set(int i, int v)
    {
        set(i,v,0,0,size);
    }
    
    
    
    ll sum(int l, int r, int x, int lx, int rx)
    {
        if (lx>=r || l>=rx)return 0;    //do not intersect
        
        if (lx>=l && rx<=r) return sums[x];
        
        int m = (lx+rx)/2;
        ll s1 = sum(l,r, 2*x+1, lx,m);
        ll s2 = sum(l,r,2*x+2, m,rx);
        return s1+s2;
    }
    
    ll sum(int l, int r)
    {
        return sum(l,r,0,0,size);
    }
    
};





int main()
{
 
    
}

