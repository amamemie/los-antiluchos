//si los modulos son muy grandes 1e18, cambiar por int128 las operaciones
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

// x ≡ a (mod m)
// x ≡ b (mod n)
//si retorna {0, -1} -> no solution
pair<ll,ll> CRT(ll a, ll m, ll b, ll n) {
    ll x, y;
    ll g = extgcd(m, n, x, y);

    if ((b - a) % g != 0)
        return {0, -1};

    ll n2 = n / g;

    ll t = ((b - a) / g * x) % n2;
    if (t < 0) t += n2;

    ll mod = m * n2;
    ll r = (a + m * t) % mod;
    if (r < 0) r += mod;

    return {r, mod};
}

// x ≡ a[i] (mod m[i]) para todo i
//vector de valores y vector de respectivos modulos
pair<ll,ll> CRT(vector<ll> a, vector<ll> m) {
    ll r = a[0];
    ll mod = m[0];

    for (int i = 1; i < a.size(); i++) {
        pair<ll,ll> res = CRT(r, mod, a[i], m[i]);

        if (res.second == -1)
            return {0, -1};

        r = res.first;
        mod = res.second;
    }

    return {r, mod};
}

void solve(){
    vector<ll>a(2);
    vector<ll>m(2);
    repl(i,0,2){
        cin >> a[i] >> m[i];
    }
    pair<ll,ll> ans = CRT(a, m);
    if(ans.second == -1){
        cout << "-1\n";
    }
    else{
        cout << ans.first << " " << ans.second << "\n";
    }
}