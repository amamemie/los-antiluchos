struct pt {
    ll x, y;
    bool operator == (const pt & o) const {
        return x == o.x and y == o.y;
    }
};

struct CustomHashPoint {
    size_t operator()(const pt & p) const {
        static
        const uint64_t C =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t x = p.x;
        uint64_t y = p.y;
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9;
        x ^= x >> 27;
        x *= 0x94d049bb133111eb;
        x ^= x >> 31;
        y ^= y >> 30;
        y *= 0xbf58476d1ce4e5b9;
        y ^= y >> 27;
        y *= 0x94d049bb133111eb;
        y ^= y >> 31;
        return C ^ (x + (y << 1));
    }
};

ll dist2(pt a, pt b) {
    ll x = a.x - b.x;
    ll y = a.y - b.y;
    return x * x + y * y;
}

pair < int, int > closest_pair(vector < pt > p) {
    int n = p.size();
    unordered_map < pt, int, CustomHashPoint > mp;
    // puntos repetidos
    for (int i = 0; i < n; i++) {
        if (mp.count(p[i]))
            return {
                mp[p[i]],
                i
            };
        mp[p[i]] = i;
    }
    mt19937 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );
    auto rnd = [ & ]() {
        return uniform_int_distribution < int > (0, n - 1)(rng);
    };
    ll d2 = dist2(p[0], p[1]);
    pair < int, int > ans = {
        0,
        1
    };
    auto upd = [ & ](int i, int j) {
        ll nd = dist2(p[i], p[j]);
        if (nd < d2) {
            d2 = nd;
            ans = {
                i,
                j
            };
        }
    };
    // conseguir una distancia inicial razonable
    for (int it = 0; it < 20; it++) {
        int i = rnd();
        int j = rnd();
        while (i == j) j = rnd();
        upd(i, j);
    }
    ll d = sqrtl((long double) d2) + 1;
    unordered_map < pt, vector < int > , CustomHashPoint > grid;
    grid.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        grid[{
            p[i].x / d,
            p[i].y / d
        }].push_back(i);
    }
    for (auto & [c, v]: grid) {
        // misma celda
        for (int i = 0; i < (int) v.size(); i++) {
            for (int j = i + 1; j < (int) v.size(); j++) {
                upd(v[i], v[j]);
            }
        }
        // celdas vecinas
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 and dy == 0) continue;
                pt to = {
                    c.x + dx,
                    c.y + dy
                };
                auto it = grid.find(to);
                if (it == grid.end()) continue;
                for (int i: v) {
                    for (int j: it -> second) {
                        upd(i, j);
                    }
                }
            }
        }
    }
    return ans;
}