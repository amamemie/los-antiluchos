map<ll, ll> fact;

ll pote(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (__int128)ans * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return ans;
}

ll mcd(ll a, ll b) {
    a = abs(a);
    b = abs(b);
    while (a != 0) {
        ll r = b % a;
        b = a;
        a = r;
    }
    return b;
}

//Rabin Miller
bool primo(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    ll D = n - 1, S = 0;
    while (D % 2 == 0) {
        D /= 2;
        S++;
    }
    static const ll STEPS = 16ll;
    for(ll pasos = 0; pasos < STEPS; pasos++){
        const ll A = 1 + rand() % (n - 1);
        ll M = pote(A, D, n);
        if (M == 1 || M == (n - 1)) goto next;
        for(ll k = 0; k < S-1; k++){
            M = (__int128)M * M % n;
            if (M == (n - 1)) goto next;
        }
        return false;
    next:;
    }
    return true;
}

//Rho de pollard
ll factor(ll n) {
    static ll A, B;
    A = 1 + rand() % (n - 1);
    B = 1 + rand() % (n - 1);
    #define fun(x) (((__int128)(x) * ((x) + B)) % n + A) 

    ll x = 2, y = 2, d = 1;
    while (d == 1 || d == -1) {
        x = fun(x);
        y = fun(fun(y));
        d = mcd(x - y, n);
    }
    return abs(d);
}

void factorize(ll n){
    assert(n > 0);
    while (n > 1 && !primo(n)) {
        ll fx;
        do {
            fx = factor(n);
        } while (fx == n);

        n /= fx;
        factorize(fx);

        for (auto &it : fact) {
            while (n % it.first == 0) {
                n /= it.first;
                it.second++;
            }
        }
    }
    if (n > 1) fact[n]++;
}
