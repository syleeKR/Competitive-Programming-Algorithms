

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int inf = INT_MAX;

//typedef int item
struct item{      //values that the node should contain is put together into item
    long long  seg, pref, suf,sum;
};

struct segtree
{
    int size;
    vector<item> values;
    
    //   "just change this part"   //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    item NEUTRAL_ELEMENT = {0,0,0,0};
    
    item merge(item a, item b)
    {
        return {
            max(a.seg, max(b.seg, a.suf+b.pref)),
            max(a.pref, a.sum+b.pref),
            max(b.suf, b.sum+a.suf),
            a.sum+b.sum
        };
    }
    
    item single(int v)
    {
        if (v>0) return {v,v,v,v};
        else return {0,0,0,v};
    }
    
    //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
    
    void init(int n)
    {
        size=1;
        while (size<n)
        {
            size*=2;
        }
        values.resize(size*2);
    }
    
    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx-lx==1)
        {
            if (lx<(int)a.size())
            {
                values[x] = single(a[lx]);
            }
            return;
        }
        
        
        int m = (lx+rx)/2;
        build(a,2*x+1, lx,m);
        build(a,2*x+2, m, rx);
        values[x] = merge(values[2*x+1], values[2*x+2]);
    }
    
    void build(vector<int> &a)
    {
        build(a, 0,0,size);
    }
    
    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx-lx==1){    //leaf node
            values[x]=single(v);
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
        
        values[x] = merge( values[2*x+1], values[2*x+2]);
    }
    
    
    void set(int i, int v)
    {
        set(i,v,0,0,size);
    }
    
    
    
    item calc(int l, int r, int x, int lx, int rx)
    {
        if (lx>=r || l>=rx)return NEUTRAL_ELEMENT;    //do not intersect
        
        if (lx>=l && rx<=r) return values[x];
        
        int m = (lx+rx)/2;
        item a = calc(l,r, 2*x+1, lx,m);
        item b = calc(l,r,2*x+2, m,rx);
        
        return merge(a,b);

        
    }
    
    
    item calc(int l, int r)
    {
        return calc(l,r,0,0,size);
    }
    
};





int main()
{

    
}





