//minimo costo de un mst dirigido:

struct Edge {
    int u, v;
    ll w;
};

ll chu_liu_edmonds(int n, int root, vector<Edge> edges) {
    ll ans = 0;
    while (true) {
        vector<ll> in(n, inf);
        vector<int> pre(n, -1);
        for (auto e : edges) {
            if (e.u != e.v and e.v != root and e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i == root) continue;
            if (in[i] == inf) return -1;
        }
        for (int i = 0; i < n; i++) {
            if (i != root) ans += in[i];
        }
        int cnt = 0;
        vector<int> id(n, -1), vis(n, -1);
        for (int i = 0; i < n; i++) {
            int v = i;
            while (v != root and vis[v] != i and id[v] == -1) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root and id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u]) {
                    id[u] = cnt;
                }
                id[v] = cnt++;
            }
        }
        if (cnt == 0) break;
        for (int i = 0; i < n; i++) {
            if (id[i] == -1) id[i] = cnt++;
        }
        vector<Edge> nxt;
        for (auto e : edges) {
            int u = id[e.u];
            int v = id[e.v];
            ll w = e.w;
            if (u != v) {
                if (id[e.v] != id[e.u]) {
                    w -= in[e.v];
                }
                nxt.push_back({u, v, w});
            }
        }
        root = id[root];
        n = cnt;
        edges = move(nxt);
    }
    return ans;
}
