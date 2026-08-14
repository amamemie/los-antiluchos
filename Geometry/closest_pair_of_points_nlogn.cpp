struct pt {
    ll x, y;
    int id;
};

ll dist2(pt a, pt b) {
    ll x = a.x - b.x;
    ll y = a.y - b.y;
    return x * x + y * y;
}

pair < int, int > closest_pair(vector < pt > p) {
    int n = p.size();
    sort(p.begin(), p.end(), [](pt a, pt b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    set < pair < ll, int >> s; // {y,id}
    ll d2 = dist2(p[0], p[1]);
    pair < int, int > ans = {
        p[0].id,
        p[1].id
    };
    int l = 0;
    for (int i = 0; i < n; i++) {
        ll d = sqrtl((long double) d2) + 1;
        // sacar puntos que ya están demasiado lejos en x
        while (l < i and p[i].x - p[l].x >= d) {
            s.erase({
                p[l].y,
                p[l].id
            });
            l++;
        }
        // buscar puntos con y cerca
        auto it = s.lower_bound({
            p[i].y - d,
            -1
        });
        while (it != s.end() and it -> first <= p[i].y + d) {
            int j = it -> second;
            ll nd = dist2(p[i], p[j]);
            if (nd < d2) {
                d2 = nd;
                ans = {
                    p[i].id,
                    p[j].id
                };
                d = sqrtl((long double) d2) + 1;
            }
            it++;
        }
        s.insert({
            p[i].y,
            p[i].id
        });
    }
    return ans;
}