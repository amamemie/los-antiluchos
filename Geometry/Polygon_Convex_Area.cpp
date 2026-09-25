ll area2(vector<point>& p) {
    ll s = 0;
    int n = p.size();

    for (int i = 0; i < n; i++)
        s += p[i] ^ p[(i + 1) % n];

    return abs(s);
}
