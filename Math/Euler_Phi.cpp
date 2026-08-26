ll phi(ll n) {
    ll ans = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            ans -= ans / p;
            while (n % p == 0){
                n /= p;
            }
        }
    }
    if (n > 1){
        ans -= ans / n;
    }
    return ans;
}