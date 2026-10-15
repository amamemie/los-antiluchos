// mst con prim
vector<ll> dist(n,inf);
vector<int> vis(n,0);
dist[0] = 0;
for(int i = 0 ; i < n ; i ++){
	int u = -1;
	for(int j = 0; j < n; j ++){
		if(!vis[j] and (u == -1 or dist[j] < dist[u]))u = j;
	}
	vis[u] = 1;
	for(int j = 0 ; j < n ; j++){
		if(vis[j])continue;
		dist[j] = min(dist[j], v[u].dist(v[j]));
	}
}
