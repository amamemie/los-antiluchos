map<long long, long long> fact;

long long mcd(long long a, long long b) {
    a = abs(a);
    b = abs(b);
    while (a != 0) {
        long long r = b % a;
        b = a;
        a = r;
    }
    return b;
}
//Rabin Miller
bool primo(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    long long D = n - 1, S = 0;
    while (D % 2 == 0) {
        D /= 2;
        S++;
    }
    static const long long STEPS = 16ll;
    for(long long pasos = 0; pasos < STEPS; pasos++){
        const long long A = 1 + rand() % (n - 1);
        long long M = pote(A, D, n);
        if (M == 1 || M == (n - 1)) goto next;
        for(long long k = 0; k < S-1; k++){
            M = ((M) * M) % n;
            if (M == (n - 1)) goto next;
        }
        return false;
    next:;
    }
    return true;
}

//Rho de pollard
long long factor(long long n) {
    static long long A, B;
    A = 1 + rand() % (n - 1);
    B = 1 + rand() % (n - 1);
    #define fun(x) (((x) * (x + B)) % n + A) 

    long long x = 2, y = 2, d = 1;
    while (d == 1 || d == -1) {
        x = fun(x);
        y = fun(fun(y));
        d = mcd(x - y, n);
    }
    return abs(d);
}

void factorize(long long n){
    assert(n > 0);
    while (n > 1 && !primo(n)) {
        long long fx;
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
