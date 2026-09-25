bool cruzan(point a, point b, point c, point d) {
    ll x = (b-a) ^ (c-a);
    ll y = (b-a) ^ (d-a);
    ll z = (d-c) ^ (a-c);
    ll w = (d-c) ^ (b-c);

    if (((x > 0) != (y > 0)) &&
        ((z > 0) != (w > 0)))
        return true;

    if (x == 0 && on_segment(a,b,c)) return true;
    if (y == 0 && on_segment(a,b,d)) return true;
    if (z == 0 && on_segment(c,d,a)) return true;
    if (w == 0 && on_segment(c,d,b)) return true;

    return false;
}
