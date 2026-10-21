int n, q;
cin >> n >> q;
DSU dsu(n + q + 10);
vector<int> id(n + 1),box(n + q + 10);
int nodes = n;
iota(id.begin(), id.end(), 0);
iota(box.begin(), box.end(), 0);
for(int i = 0 ;  i < q ; i ++){
    int a, b;
    cin >> a >> b;
    int ori = id[a];
    int ori2 = id[b];
    dsu.parent[ori] = ori2;
    nodes++;
    id[a] = nodes;
    box[nodes] = a;
}
for(int i = 1; i  <= n  ; i ++){
    cout << box[dsu.find(i)] << ' ';
}
