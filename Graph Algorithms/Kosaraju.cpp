struct Kosaraju {
    int n, components;
    vector<vector<int>> graph, invgraph;
    vector<int> vis, order, component;

    Kosaraju(int n) : n(n) {
        graph.resize(n + 1);
        invgraph.resize(n + 1);
        vis.resize(n + 1);
        component.resize(n + 1);
    }

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        invgraph[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = 1;
        for (int v : graph[u]) {
            if (!vis[v])
                dfs1(v);
        }
        order.push_back(u);
    }

    void dfs2(int u, int id) {
        vis[u] = 1;
        component[u] = id;
        for (int v : invgraph[u]) {
            if (!vis[v])
                dfs2(v, id);
        }
    }
    void build() {
        for (int u = 1; u <= n; u++) {
            if (!vis[u])
                dfs1(u);
        }
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), 0);
        components = 0;
        for (int u : order) {
            if (!vis[u]) {
                components++;
                dfs2(u, components);
            }
        }
    }
};
