struct TwoSAT {
    int n, nodes;
    vector<vector<int>> graph, invgraph;
    vector<int> vis, order, component;
    vector<bool> ans;

    TwoSAT(int n) : n(n), nodes(2 * n) {
        graph.resize(nodes);
        invgraph.resize(nodes);
        vis.resize(nodes);
        component.resize(nodes);
        ans.resize(n);
    }

    int id(int x, bool value) {
        return 2 * x + value;
    }

    int neg(int x) {
        return x ^ 1;
    }

    void add_implication(int a, int b) {
        graph[a].push_back(b);
        invgraph[b].push_back(a);
    }

    void add_or(int a, int b) {
        add_implication(neg(a), b);
        add_implication(neg(b), a);
    }

    void add_xor(int a, int b) {
        add_or(a, b);
        add_or(neg(a), neg(b));
    }

    void add_equivalence(int a, int b) {
        add_implication(a, b);
        add_implication(b, a);
        add_implication(neg(a), neg(b));
        add_implication(neg(b), neg(a));
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

    bool solve() {
        for (int u = 0; u < nodes; u++) {
            if (!vis[u])
                dfs1(u);
        }
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), 0);
        int cnt = 0;
        for (int u : order) {
            if (!vis[u]) {
                dfs2(u, cnt++);
            }
        }
        for (int i = 0; i < n; i++) {
            if (component[2 * i] == component[2 * i + 1])
                return false;
            ans[i] = component[2 * i] > component[2 * i + 1];
        }
        return true;
    }
};
