const double PI = acos(-1);

void fft(vector<complex<double>>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (complex<double>& x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<complex<double>> fa(a.begin(), a.end());
    vector<complex<double>> fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, 0);
    fft(fb, 0);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, 1);
    vector<int> res(n);
    for (int i = 0; i < n; i++)
        res[i] = round(fa[i].real());
    return res;
}

//ejemplo :

void solve(){
    int n;
    cin >> n;

    vector<int> v(n);
    int mx = 0;

    for(int i = 0; i < n; i++){
        cin >> v[i];
        mx = max(mx, v[i]);
    }

    vector<int> pol(mx + 1);

    for(auto x : v)
        pol[x] = 1;

    pol = multiply(pol, pol);

    int m;
    cin >> m;

    int ans = 0;

    for(int i = 0; i < m; i++){
        int x;
        cin >> x;

        if(x < pol.size() and pol[x] > 0)
            ans++;
    }

    cout << ans << '\n';
}
