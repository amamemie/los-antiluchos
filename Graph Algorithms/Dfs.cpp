const int N = 1e5;

vector<int> G[N];
int vis[N];

void dfs(int u){
    vis[u] = 1;
    for(int v : G[u]){
        if(vis[v] == -1){
            dfs(v);
        }
    }
}
