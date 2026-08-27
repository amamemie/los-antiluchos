struct BIT{
    ll n;
    vector<vector<ll>> xs;
    vector<vector<ll>> bit;
    BIT(ll nn){
        n = nn;
        xs.resize(n + 1);
        bit.resize(n + 1);
    }
    void prepare(ll x, ll y){
        for (ll i = x; i <= n; i += (i&(-i))){
            xs[i].push_back(y);
        }
    }
    void build(){
        for (ll i = 1; i <= n; i++){
            sort(xs[i].begin(), xs[i].end());
            xs[i].erase(unique(xs[i].begin(), xs[i].end()), xs[i].end());
            bit[i].assign(xs[i].size() + 1, 0);
        }
    }
    void add(ll x, ll y, ll val){
        for (ll i = x; i <= n; i += (i&(-i))){
            ll p = lower_bound(xs[i].begin(), xs[i].end(), y) - xs[i].begin() + 1;
            for (ll j = p; j < bit[i].size(); j += (j&(-j))){
                bit[i][j] += val;
            }
        }
    }
    ll sum(ll x, ll y){
        ll ans = 0ll;
        for (ll i = x; i > 0; i -= (i&(-i))){
            ll p = lower_bound(xs[i].begin(), xs[i].end(), y) - xs[i].begin();
            for (ll j = p; j > 0; j -= (j&(-j))){
                ans += bit[i][j];
            }
        }
        return ans;
    }
    ll query(ll x1, ll y1, ll x2, ll y2){
        return sum(x2-1,y2) - sum(x2-1, y1) - sum(x1 - 1, y2) + sum(x1 - 1, y1);
    }

};
void solve(int tc){
    int n,q; cin >> n >> q;
    set<ll> X;
    set<ll> Y;
    vector<vector<ll>> points;
    vector<vector<ll>> query;
    repl(i,0,n){
        ll x,y,w; cin >> x >> y >> w;
        X.insert(x);
        Y.insert(y);
        points.push_back({x,y,w});
    }
    repl(i,0,q){
        int t; cin >> t;
        if(t == 0){
            ll x,y,w; cin >> x >> y >> w;
            X.insert(x);
            Y.insert(y);
            query.push_back({0,x,y,w});
        }
        else{
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            X.insert(x1);
            X.insert(x2);
            Y.insert(y1);
            Y.insert(y2);
            query.push_back({1,x1,y1,x2,y2});
        }
    }
    map<ll,ll> equis, ye;
    int i = 0;
    for(ll x : X){
        i++;
        equis[x] = i;
    }
    i = 0;
    for(ll x : Y){
        i++;
        ye[x] = i;
    }
    BIT bit((ll)X.size());
    for(auto &x : points){
        x[0] = equis[x[0]];
        x[1] = ye[x[1]];
        bit.prepare(x[0], x[1]);
    }
    for(auto &x : query){
        if(x[0] == 0){
            x[1] = equis[x[1]];
            x[2] = ye[x[2]];
            bit.prepare(x[1], x[2]);
        }
        else{
            x[1] = equis[x[1]];
            x[2] = ye[x[2]];
            x[3] = equis[x[3]];
            x[4] = ye[x[4]];
        }
    }
    bit.build();
    for(auto &x : points){
        bit.add(x[0], x[1], x[2]);
    }
    for(auto &x : query){
        if(x[0] == 0){
            bit.add(x[1], x[2], x[3]);
        }
        else{
            cout << bit.query(x[1],x[2],x[3],x[4]) << "\n";
        }
    }
}
