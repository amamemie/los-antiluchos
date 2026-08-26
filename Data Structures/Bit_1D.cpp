struct BIT{
    int n; 
    vector<ll> bit;
    BIT(int _n){
        n = _n;
        bit.assign(n + 1, 0);
    }
    void add(int x, ll val){
        for (int i = x; i <= n; i += (i&(-i))){
            bit[i] += val;
        }
        
    }
    ll sum(int x){
        ll ans = 0ll;
         for (int i = x; i > 0; i -= (i&(-i))){
            ans += bit[i];
        }
        return ans;
    }
    ll query(int l, int r){
        return sum(r) - sum(l - 1);
    }
};
