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



struct Graph
{
    /*        members of graph           */
    
    int v;    //number of vertex
    int e;    // number of edges
    vector<int> adj[MxN+1];   //adjacency list
    vector<pii> wadj[MxN+1];  //adjacency list of weighted graph
    
    vector<int> dist;           //storing distance
    vector<int> color;        //0 =white, 1=gray(changes to gray at the first visit), 2=black(every node connected to it is visited)
    vector<int> pred;           // predecessor graph!. 0 means NIL
    vector<int> finish;
    vector<int> discover;
    
    vector<tuple<int, int, int>> edges; //edge list : (weight, u,v)
    
/*#########################################################################################################################################*/
    /*        initialize                 */
    
    Graph(int v):v(v)
    {
        dist.resize(v+1);
        color.resize(v+1);
        pred.resize(v+1);
        finish.resize(v+1);
        discover.resize(v+1);
    }
    
    Graph(int v, int e): v(v), e(e)
    {
        dist.resize(v+1);
        color.resize(v+1);
        pred.resize(v+1);
        finish.resize(v+1);
        discover.resize(v+1);
    }
    
    void initialize(bool directed = false)
    {
        if (directed == false){
        REP0(i,e)
        {
            int u,v;
            cin>>u>>v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        }
        else{
            REP0(i,e)
            {
                int u,v;
                cin>>u>>v;
                adj[u].pb(v);
            }
        }
    }
    
    void winitialize(bool directed =false)
    {
        if (directed == false){
        REP0(i,e)
        {
            int u,v,w;
            cin>>u>>v>>w;
            wadj[u].pb({v,w});
            wadj[v].pb({u,w});
        }
        }
        else{
            REP0(i,e)
            {
                int u,v,w;
                cin>>u>>v>>w;
                wadj[u].pb({v,w});
            }
        }
        
    }
    
    void clear()
    {
        REP1(i, v)
        {
            dist[i]=inf;
            color[i]=0;
            pred[i]=0;
        }
    }
    
    void sortedge()
    {
        REP1(i,v)
        {
            sort(adj[i].begin(), adj[i].end());
        }
    }
  
    
/*#########################################################################################################################################*/
    /*    graph traversal algorithms     */
    
    void bfs(int s)
    {
        clear();
        dist[s]=0;
        color[s]=1;
        queue<int> q;
        q.push(s);
        
        while(! q.empty())
        {
            int curr = q.front(); q.pop();
            
            //process curr here. every node is popped from queue once, entered to queue once.
            
            for (auto next : adj[curr])
            {
                if (color[next]==0)    //only white vertices can be inserted into queue. all vertices in the queue is black
                {
                    color[next]=1;
                    pred[next]=curr;
                    dist[next]=dist[curr]+1;
                    q.push(next);
                }
            }
            color[curr] = 2;   //adjacent vertices are all visited
        }
    }
    
    
    void dfs(int curr)               //simple dfs
    {
        color[curr]++;
        //process curr here
        
        for (auto next : adj[curr])
        {
            if (color[next]==0) dfs(next);  //only white vertices can be the source of dfs
        }
        
    }
    
    void dfs_visit(int curr, int & time )
    {
        time++;
        discover[curr]=time;
        color[curr] = 1; //gray
        
        //process curr here. each vertex can be called exactly once by dfs_visit.
        
        for (auto next : adj[curr])
        {
            if (color[next]==0)
            {
                pred[next] = curr;
                dfs_visit(next, time);
            }
        }
        
        color[curr]=2; //black. im done
        time++;
        finish[curr] =time;
        
        
    }
    
    void dfs()
    {
        clear();
        int time=0;
        
        REP1(i,v)
        {
            if (color[i] ==0 )    //if not visited(color ==white)
            {
                dfs_visit(i,time);
            }
        }
        
    }
    
    
/*#########################################################################################################################################*/
    /*     algorithms based on graph traversals : topological sort, SCC, articulation point, bridge, BCC    */
    void dfs_visit_topological_sort(int curr, vint& vec )
    {
        color[curr] = 1;
        for (auto next : adj[curr])
        {
            if (color[next]==0)
            {
                dfs_visit_topological_sort(next, vec);
            }
        }
        vec.pb(curr);  //when proceesing ends, we add it to vec(at the finishing time)
    }
    vint topological_sort()   //algorithm for DAG
    {
        vint vec;
        clear();
        REP1(i,v)
        {
            if (color[i] ==0 )
            {
                dfs_visit_topological_sort(i, vec);
            }
        }
        REP0(i,(int)vec.size()/2)               //reversing the vector. descending order of finish time!
        {
            swap(vec[i], vec[(int)vec.size()-1-i]);
        }
        return vec;
    }
    
    void dfs_visit_rev(int curr, vint& vec, vint radj[] )
    {
        color[curr] = 1;
        vec.pb(curr);   //insert node that we visit to vec. each vec corresponds to one component of scc
        for (auto next : radj[curr])
        {
            if (color[next]==0)
            {
                dfs_visit_rev(next, vec, radj);
            }
        }
    }
    
    vector<vint> scc()    //algorithm for DG
    {
        vector<vint> components;
        //run dfs
        vint ordered;
        ordered = topological_sort();  //run dfs, sort vertices in order of decreasing finish time
        //reverse the edges!
        vint radj[v+1];
        REP1(i, v)
        {
            for (auto x :  adj[i])
            {
                radj[x].pb(i);
            }
        }
        //run dfs again in radj
        clear();
        for (auto i : ordered)
        {
            if (color[i] ==0 )
            {
                vint vec;
                dfs_visit_rev(i, vec, radj);
                components.pb(vec);
            }
        }
        return components;
    }
    
    
    void dfs_visit_AP(int curr, int & time, vint & isitap , vint &child, vint & low)
    {
        time++;
        discover[curr]=time;
        color[curr] = 1;
        
        low[curr] = discover[curr];
        
        for (auto next : adj[curr])
        {
            if (color[next]==0)     //white vertex <-> a child in DFT
            {
                child[curr]++;
                pred[next] = curr;
                dfs_visit_AP(next, time, isitap, child, low);
                low[curr]=min(low[curr], low[next]);
                
                if (pred[curr]!=0 && low[next]>=discover[curr])   //2. if not root if one of the subtree is not connected with a back edge it is ap.
                {
                    isitap[curr]=1;
                }
            }
            else{
                low[curr]=min(low[curr], discover[next]); //핵심. back edge가 연결하고 있는 놈의 discover time을 가져와서 최소인지 확인
            }
            
        }
        
        if (pred[curr]==0 && child[curr]>=2)     //1.if root(pred=0) && more than two child ->  articulation point
        {
            isitap[curr]=1;
        }
        
        color[curr]=2;
        time++;
        finish[curr] =time;
        
        
    }
    vint articulation_points()      //for undirected graphs
    {
        vint ap;    //storing articulation points
        clear();
        
        vint isitap(v+1);
        vint child(v+1); //holds the number of child
        vint low(v+1, inf);   //holds the lowest discovery time among the vertices that can be reached from its descendants(including myself)
        
        int time=0;
        
        REP1(i,v)
        {
            if (color[i] ==0 )
            {
                dfs_visit_AP(i,time, isitap, child, low);
            }
        }
        REP1(i,v)
        {
            if(isitap[i]==1) ap.pb(i);
        }
        
        return ap;
    }
    
    void dfs_visit_bridge(int curr, int & time, vector<pii> & bridges , vint & low)
    {
        time++;
        discover[curr]=time;
        color[curr] = 1;
        
        low[curr] = discover[curr];
        
        for (auto next : adj[curr])
        {
            if (color[next]==0)     //white vertex <-> a child in DFT. only check this edge and decide to put or not
            {
                pred[next] = curr;
                dfs_visit_bridge(next, time, bridges,  low);
                low[curr]=min(low[curr], low[next]);
                
                if (low[next]>discover[curr])   //2. if not root if one of the subtree is not connected with a back edge it is ap.
                {
                    bridges.pb({min(curr, next), max(next, curr)});
                }
            }
            else{
               if (pred[curr]!=next)low[curr]=min(low[curr], discover[next]); //핵심. back edge가 연결하고 있는 놈의 discover time을 가져와서 최소인지 확인
            }
            
        }
        
    }
    vector<pii> bridges()      //for undirected graphs
    {
        vector<pii> bridges;    //storing bridges.  all edges are in form (u,v) u<v
        clear();
        
        vint low(v+1, inf);   //holds the lowest discovery time among the vertices that can be reached from its descendants(including myself)
        
        int time=0;
        
        REP1(i,v)
        {
            if (color[i] ==0 )
            {
                dfs_visit_bridge(i,time, bridges, low);
            }
        }

        return bridges;
    }


    
/*#########################################################################################################################################*/
    /*      Minimum spanning tree     */
    //O(mlogm +n)
    
    void make_edge_list()
    {
        REP1(i,v)
        {
            for(auto pair : wadj[i])
            {
                edges.pb(make_tuple(pair.se, i,pair.fi));
            }
        }
        
    }
    void kruskal()
    {
        make_edge_list();
        sort(edges.begin(), edges.end());
        DSU dsu(v);
        
        for(auto edge :edges)
        {
            int w,a,b; tie(w,a,b)=edge;
            if(!dsu.same(a,b))
            {
                dsu.unite(a,b);
                //process 
            }
        }
    }
    
    
    void Prim(int start_node)
    {
        priority_queue<pair<int, int>> pq;
        bool included[v+1];
        int distfromtree[v+1];
        for (int i=1; i<=v; i++)
        {
            included[i]=false;
            distfromtree[i]=inf;
        }

        pq.push({0,start_node});
        included[start_node]=true;
        
        
        while(!pq.empty())
        {
            int node=pq.top().second; pq.pop();
            if (included[node]) continue;
            included[node]=true;
            
            for (auto u : wadj[node])
            {
                int next = u.first; int weight = u.second;
                
                if (distfromtree[next]>distfromtree[node]+weight)
                {
                    distfromtree[next]=distfromtree[node]+weight;
                    pq.push({-distfromtree[next],next});
                }
            }
        }
    }
    
    
    
    
/*#########################################################################################################################################*/
    /*      Single source shortest path   */
        
        //O(mlogm +n)
        vector<pii> adj[MxN+1];
        int dist[MxN+1];
        int processed[MxN+1];
        int parent[MxN+1];

        void Dijkstra(int start)
        {
            for(int i=1; i<=MxN; i++)
            {
                dist[i]=inf/10;
                processed[i]=false;
                parent[i]=0;
            }
            dist[start]=0;
            
            priority_queue<pii> pq;
            pq.push({0, start});
            
            while(!pq.empty())
            {
                int curr = pq.top().se;  pq.pop();
                if(processed[curr])continue;
                processed[curr]=true;
                
                for(auto x : adj[curr])
                {
                    int node = x.fi;  int w = x.se;
                    if(dist[curr]+w<dist[node])
                    {
                        dist[node]=dist[curr]+w;
                        parent[node]=curr;
                        pq.push({-dist[node], node});
                    }
                }
            }
        }

    
    
    
/*#########################################################################################################################################*/
    /*      All pairs shortest path      */
    

    
    
    
};

