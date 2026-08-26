struct BIT {
    int n;
    int m;
    int p;
    vector < vector < vector < ll >>> bit;
    BIT(int _n) {
        n = _n + 10;
        m = _n + 10;
        p = _n + 10;
        bit.assign(n, vector < vector < ll >> (n, vector < ll > (n, 0)));
    }
    void add(int x, int y, int z, int val) {
        for (int i = x; i <= n; i += (i & (-i))) {
            for (int j = y; j <= n; j += (j & (-j))) {
                for (int k = z; k <= n; k += (k & (-k))) {
                    bit[i][j][k] += val;
                }
            }
        }
    }
    ll sum(int x, int y, int z) {
        ll ans = 0 ll;
        for (int i = x; i > 0; i -= (i & (-i))) {
            for (int j = y; j > 0; j -= (j & (-j))) {
                for (int k = z; k > 0; k -= (k & (-k))) {
                    ans += bit[i][j][k];
                }
            }
        }
        return ans;
    }
    ll query(int x1, int y1, int z1, int x2, int y2, int z2) {
        return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y2, z1 - 1) - sum(x2, y1 - 1, z2) + sum(x1 - 1, y1 - 1, z2) + sum(x2, y1 - 1, z1 - 1) + sum(x1 - 1, y2, z1 - 1) - sum(x1 - 1, y1 - 1, z1 - 1);
    }
};
