struct BIT{
    int n, m;
    vector<vector<ll>> bit;

    BIT(int _n){
        n = _n; 
        m = _n;
        bit.assign(n+1, vector<ll>(n+1 ,0));
    }
    void add(int x, int y, ll val){
        for (int i = x; i <= n; i += (i&(-i))){
            for (int j = y; j <= n; j += (j&(-j))){
                bit[i][j] += val;
            }
        }
    }
    ll sum(int x, int y){
        ll ans = 0ll;
        for (int i = x; i > 0; i -= (i&(-i))){
            for (int j = y; j > 0; j -= (j&(-j))){
                ans += bit[i][j];
            }
        }
        return ans;
    }
    ll query(int x1, int y1, int x2, int y2){
        return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
    }
};
