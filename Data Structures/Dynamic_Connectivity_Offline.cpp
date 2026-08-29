struct Change {
    int a, b, sz_a;
};

struct DSU {
    vector<int> parent, sz;
    vector<Change> history;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }

    int find(int x) {
        while (x != parent[x])
            x = parent[x];
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            history.push_back({-1, -1, -1});
            return false;
        }
        if (sz[a] < sz[b])
            swap(a, b);
        history.push_back({a, b, sz[a]});
        parent[b] = a;
        sz[a] += sz[b];
        components--;
        return true;
    }

    int snapshot() {
        return history.size();
    }

    void rollback(int snap) {
        while (history.size() > snap) {
            auto [a, b, old_sz_a] = history.back();
            history.pop_back();
            if (a == -1)
                continue;
            parent[b] = b;
            sz[a] = old_sz_a;
            components++;
        }
    }
};

struct Edge {
    int u, v;
};

struct SegmentTree {
    int n;
    vector<vector<Edge>> tree;
    SegmentTree(int n) {
        this->n = n;
        tree.resize(4 * n + 5);
    }
    void add(int node, int l, int r, int ql, int qr, Edge e) {
        if (qr < l or r < ql)
            return;
        if (ql <= l and r <= qr) {
            tree[node].push_back(e);
            return;
        }
        int mid = (l + r) / 2;
        add(node * 2, l, mid, ql, qr, e);
        add(node * 2 + 1, mid + 1, r, ql, qr, e);
    }
    void add(int l, int r, Edge e) {
        if (l > r)
            return;
        add(1, 1, n, l, r, e);
    }
};

void dfs(int node, int l, int r, SegmentTree &seg, DSU &dsu, vector<int> &answer){
    int snap = dsu.snapshot();
    for (auto [u, v] : seg.tree[node])
        dsu.unite(u, v);
    if (l == r) {
        answer[l] = dsu.components;
    } else {
        int mid = (l + r) / 2;
        dfs(node * 2, l, mid, seg, dsu, answer);
        dfs(node * 2 + 1, mid + 1, r, seg, dsu, answer);
    }
    dsu.rollback(snap);
}

void solve() {
    int n, q;
    cin >> n >> q;
    if (q == 0)
        return;
    DSU dsu(n);
    SegmentTree seg(q);
    map<pair<int,int>, int> start;
    vector<int> answer(q + 1);
    vector<bool> query(q + 1);
    for (int t = 1; t <= q; t++) {
        char type;
        cin >> type;
        if (type == '?') {
            query[t] = true;
        } else {
            int u, v;
            cin >> u >> v;
            if (u > v)
                swap(u, v);
            if (type == '+') {
                start[{u, v}] = t;
            } else {
                int L = start[{u, v}];
                seg.add(L, t - 1, {u, v});
                start.erase({u, v});
            }
        }
    }
    for (auto [edge, L] : start) {
        auto [u, v] = edge;
        seg.add(L, q, {u, v});
    }
    dfs(1, 1, q, seg, dsu, answer);
    for (int t = 1; t <= q; t++) {
        if (query[t])
            cout << answer[t] << '\n';
    }
}
