void solve(){
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    ll suma = 0, sumb = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        suma += a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        sumb += b[i];
    }
    vector<ll> aa(2 * n);
    vector<ll> ae(2 * n);
    for(int i = 0; i < n; i++){
        aa[i] = aa[i + n] = a[i];
        ae[i] = ae[i + n] = (a[i] != 0);
    }
    vector<ll> be(n);
    vector<ll> rev_b(n);
    for(int i = 0; i < n; i++){
        be[i] = (b[n - 1 - i] != 0);
        rev_b[i] = b[n - 1 - i];
    }
    vector<ll> conv1 = multiply(aa, be);
    vector<ll> conv2 = multiply(ae, rev_b);
    ll ans = 0;
    for(int rot = 0; rot < n; rot++){
        int pos = n - 1 + rot;
        ll perdida = conv1[pos] + conv2[pos];
        ans = max(ans, suma + sumb - perdida);
    }
    cout << ans << '\n';
}
