pair<ll,ll> pick(vector<point>& v) {
    ll B = 0, A2 = 0;
    ll n = v.size();

    for (ll i = 0; i < n; i++) {
        ll j = (i + 1) % n;
        B += __gcd(abs(v[i].x - v[j].x),
                   abs(v[i].y - v[j].y));
    }

    for (ll i = 2; i < n; i++)
        A2 += (v[i] - v[0]) ^ (v[i-1] - v[0]);

    A2 = abs(A2);

    ll I = (A2 - B + 2) / 2;

    return {I, B};
}
