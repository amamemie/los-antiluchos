const int N = 1e5;

vector<int> G[N];
int vis[N];
void bfs(int source){
    queue<int> q;
    q.push(source);
    vis[source] = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : G[u]){
            if(vis[v] == -1){
                vis[v] = vis[u] + 1;
                q.push(v);
            }
        }
    }
}
