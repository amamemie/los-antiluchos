bool cruzan(point a, point b, point c, point d) {
    double x = (b-a) ^ (c-a);
    double y = (b-a) ^ (d-a);
    double z = (d-c) ^ (a-c);
    double w = (d-c) ^ (b-c);

    if ((x > 0 && y > 0) || (x < 0 && y < 0)) return false;

    if (x == 0 && y == 0) {
        if (a < c && a < d && b < c && b < d) return false;
        if (c < a && c < b && d < a && d < b) return false;
        return true;
    }

    return !((z > 0 && w > 0) || (z < 0 && w < 0));
}

bool estamid(point p, point a, point b) {
    if (b < a) swap(a, b);
    return p.left(a, b) == 2 && a < p && p < b;
}

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<point> v(n);
    repl(i, 0, n) cin >> v[i].x >> v[i].y;

    repl(i, 0, m) {
        point p;
        cin >> p.x >> p.y;

        double a = (rand() % 9 + 1) / 10.0;
        double b = (rand() % 9 + 1) / 10.0;
        point q(p.x + b, 1e18 + a);

        ll cnt = 0;
        bool boundary = false;

        repl(j, 0, n) {
            ll k = (j + 1) % n;

            cnt += cruzan(p, q, v[j], v[k]);

            if (estamid(p, v[j], v[k]) ||
                p.x == v[j].x && p.y == v[j].y ||
                p.x == v[k].x && p.y == v[k].y)
                boundary = true;
        }

        if (boundary) cout << "BOUNDARY\n";
        else if (cnt & 1) cout << "INSIDE\n";
        else cout << "OUTSIDE\n";
    }
}
