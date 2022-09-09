/*
 Disjoint set union
 
 with union by rank & path compression
 
 find, set, unite is all done in O(1) time. (inverse of ackermann ftn)
 
 */

struct DSU
{
    int n;                //n elements : 1~n
    vector<int> link;
    vector<int> size;
    
    DSU(int n):n(n)       //make n sets
    {
        link.resize(n+1);
        size.resize(n+1);
        for(int i=1; i<=n; i++) link[i]=i;
        for(int i=1; i<=n; i++) size[i]=1;
    }
    
    int find(int x)       //find the representing node for the set & path compression
    {
        if (link[x]!=x)
        {
            link[x] = find(link[x]);
        }
        
        return link[x];
    }

    bool same(int a, int b)
    {
        return find(a)==find(b);
    }
    
    
    void unite(int a, int b)         //union by rank(size)
    {
        a = find(a); b= find(b);
        if(a!=b){
        if (size[a]<size[b]) swap(a,b);
        link[b] = a;
        size[a] +=size[b];
        }
    }

};

