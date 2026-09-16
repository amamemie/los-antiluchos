vector<vector<int>> g;
vector<int> tin, low;
vector<bool> vis;
vector<pair<int,int>> bridges;

int timer = 0;

void dfs(int u, int p = -1){
    vis[u] = true;
    tin[u] = low[u] = timer++;

    for(int v : g[u]){
        if(v == p) continue;

        if(vis[v]){
            // Arista hacia un ancestro
            low[u] = min(low[u], tin[v]);
        }
        else{
            dfs(v, u);

            // El subárbol de v puede llegar hasta...
            low[u] = min(low[u], low[v]);

            // Si no puede regresar a u ni a un ancestro de u,
            // entonces (u,v) es puente
            if(low[v] > tin[u]){
                bridges.push_back({u, v});
            }
        }
    }
}