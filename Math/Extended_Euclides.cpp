//Encuentra
//valores para x e y
//A*x + B*y = gcd(A, B)
ll extgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
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

void solve(){
    ll A, B, C;
    cin >> A >> B >> C;
    ll x, y;
    ll g = extgcd(A, B, x, y);
    if(C % g != 0){
        cout << "-1\n";
        return;
    }
    ll k = -C / g;
    x *= k;
    y *= k;
    cout << x << " " << y << '\n';
}