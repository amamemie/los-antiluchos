ll const MOD = 1e9+7;

struct Mat {
    int n;
    vector<vector<unsigned int>> a;

    Mat(int n, bool id = false) : n(n), a(n, vector<unsigned int>(n, 0)) {
        if (id) for (int i = 0; i < n; i++) a[i][i] = 1;
    }

    Mat operator*(const Mat& o) const {
        Mat r(n);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) {
                if (a[i][k] == 0) continue;
                for (int j = 0; j < n; j++)
                    r.a[i][j] = (r.a[i][j] + a[i][k] * o.a[k][j])%MOD;
            }
        return r;
    }
};

Mat mpow(Mat b, ll e) {
    Mat r(b.n, true);
    while (e) {
        if (e & 1) r = r * b;
        b = b * b;
        e >>= 1;
    }
    return r;
}
