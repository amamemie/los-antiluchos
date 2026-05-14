struct Dinic
{
    const int INF = 1e9;

    struct flowEdge
    {
        int to, rev, f, cap;
    };

    vector<vector<flowEdge>> G;
    vector<int> work, lvl, Q;
    
    int S, T, nodes;

    Dinic(){}
    Dinic(int n, int s, int t){
        S = s;
        T = t;
        nodes = n;
        G.clear();
        G.resize(n);
        Q.resize(n);
    }
    void addEdge(int st, int en , int cap){
        flowEdge A = {en, (int)G[en].size(), 0, cap};
        flowEdge B = {st, (int)G[st].size(), 0, 0};
        G[st].pb(A);
        G[en].pb(B);
    }
    int dfs(int v, int f){
        if(v == T or f == 0) return f;
        for(int &i = work[v]; i < G[v].size(); i++){
            flowEdge &e = G[v][i];
            int u = e.to;
            if(e.cap <= e.f or lvl[u] != lvl[v] + 1) continue;
            int df = dfs(u, min(f, e.cap - e.f));
            if(df){
                e.f += df;
                G[u][e.rev].f -= df;
                return df;
            }
        }
        return 0;
    }
    bool bfs(){
        int qt = 0;
        Q[qt++] = S;
        lvl.assign(nodes,-1);
        lvl[S] = 0;
        for(int i = 0; i < qt; i++){
            int u = Q[i];
            for(flowEdge &e : G[u]){
                int v = e.to;
                if(e.cap <= e.f or lvl[v] != -1) continue;
                lvl[v] = lvl[u] + 1;
                Q[qt++] = v;
            }
        }
        return lvl[T] != -1;
    }
    int maxFlow(){
        int flow = 0;
        while(bfs()){
            work.assign(nodes,0);
            while(true){
                int df = dfs(S,INF);
                if(df == 0) break;
                flow += df; 
            }
        } 
        return flow;
    }
    
};
