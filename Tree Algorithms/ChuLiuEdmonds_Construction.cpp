// construccion de mst dirigido

const ll inf = 1e18;

struct ChuLiuEdmonds {
    struct Edge {
        int u, v;
        ll w;
    };

    struct Result {
        bool ok;
        ll cost;
        vector<Edge> mst;
    };

    int n;
    vector<Edge> edges;

    ChuLiuEdmonds(int n) : n(n) {}

    void add_edge(int u, int v, ll w) {
        edges.push_back({u - 1, v - 1, w});
    }

    struct E {
        int u, v;
        ll w;
        int id;
    };

    struct Sol {
        bool ok;
        vector<int> chosen;
    };

    Sol dfs(int n, int root, vector<E>& edges) {
        vector<ll> in(n, inf);
        vector<int> pre(n, -1), id(n, -1), vis(n, -1);
        for (int i = 0; i < (int)edges.size(); i++) {
            auto e = edges[i];
            if (e.u != e.v and e.v != root and e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }
        in[root] = 0;
        for (int i = 0; i < n; i++) {
            if (in[i] == inf) return {false, {}};
        }
        int cnt = 0;
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
        if (cnt == 0) {
            vector<int> chosen;
            for (int i = 0; i < n; i++) {
                if (i != root) {
                    int idx = -1;
                    for (int j = 0; j < (int)edges.size(); j++) {
                        if (edges[j].v == i and
                            edges[j].u == pre[i] and
                            edges[j].w == in[i]) {
                            idx = j;
                            break;
                        }
                    }
                    chosen.push_back(idx);
                }
            }
            for (int x : chosen) {
                if (x == -1) return {false, {}};
            }
            return {true, chosen};
        }
        for (int i = 0; i < n; i++) {
            if (id[i] == -1) id[i] = cnt++;
        }
        vector<E> nxt;
        for (int i = 0; i < (int)edges.size(); i++) {
            auto e = edges[i];
            int u = id[e.u];
            int v = id[e.v];
            if (u != v) {
                nxt.push_back({u, v,e.w - in[e.v],i});
            }
        }
        Sol res = dfs(cnt, id[root], nxt);
        if (!res.ok) return {false, {}};
        vector<int> chosen(n, -1);
        for (int i = 0; i < n; i++) {
            if (i != root) {
                for (int j = 0; j < (int)edges.size(); j++) {
                    if (edges[j].v == i and
                        edges[j].u == pre[i] and
                        edges[j].w == in[i]) {
                        chosen[i] = j;
                        break;
                    }
                }
                if (chosen[i] == -1) return {false, {}};
            }
        }
        for (int j : res.chosen) {
            int old_idx = nxt[j].id;
            chosen[edges[old_idx].v] = old_idx;
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (i != root) {
                if (chosen[i] == -1) return {false, {}};
                ans.push_back(chosen[i]);
            }
        }
        return {true, ans};
    }

    Result get_mst(int root) {
        vector<E> e;
        for (int i = 0; i < (int)edges.size(); i++) {
            e.push_back({edges[i].u,edges[i].v,edges[i].w,i});
        }
        Sol res = dfs(n, root - 1, e);
        if (!res.ok) return {false, -1, {}};
        Result ans;
        ans.ok = true;
        ans.cost = 0;
        for (int i : res.chosen) {
            auto x = edges[i];
            ans.cost += x.w;
            ans.mst.push_back({x.u + 1, x.v + 1, x.w});
        }
        return ans;
    }

    bool possible(int root) {
        return get_mst(root).ok;
    }

    ll get_min_cost(int root) {
        Result res = get_mst(root);
        return res.ok ? res.cost : -1;
    }
};
