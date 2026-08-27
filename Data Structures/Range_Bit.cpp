struct RangeBIT{
    int n;
    vector<ll> bit1, bit2;
    RangeBIT(int nn){
        n = nn;
        bit1.assign(n + 1,0);
        bit2.assign(n + 1,0);
    }
    void add_one(vector<ll> &b, int x, ll val){
        for (int i = x; i <= n; i+= (i&(-i))){
            b[i] += val;
        }
    }
    void add(int l, int r, ll val){
        add_one(bit1, l, val);
        add_one(bit1, r + 1, -val);
        add_one(bit2, l, l * val);
        add_one(bit2, r + 1, -(r + 1) * val);
    }
    ll sum_one(const vector<ll> &b, int x){
        ll ans = 0ll;
        for (int i = x; i > 0; i -= (i&(-i))){
            ans += b[i];
        }
        return ans;
    }

    ll sum(int x){
        return (x + 1) * sum_one(bit1,x) - sum_one(bit2, x);
    }
    ll query(int l, int r){
        return sum(r) - sum(l - 1);
    }
};
