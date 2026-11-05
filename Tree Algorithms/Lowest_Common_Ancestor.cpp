const int N = 2e5+10;
const int LOG = 20;
vector<int> G[N];
int depth[N], up[N][LOG];
 
void dfs(int u, int p){
    up[u][0] = p;
    for(int j = 1; j < LOG; j++)
        up[u][j] = up[up[u][j-1]][j-1];
    for(int v : G[u]){
        if(v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
 
int get_lca(int a, int b){
    if(depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    for(int j = 0; j < LOG; j++)
        if(k >> j & 1) a = up[a][j];
    if(a == b) return a;
    for(int j = LOG-1; j >= 0; j--)
        if(up[a][j] != up[b][j]){
            a = up[a][j];
            b = up[b][j];
        }
    return up[a][0];
}
