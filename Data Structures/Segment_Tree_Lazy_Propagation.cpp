const int N = 1e5;

struct info {
    long long num;
};

info ST[4 * N];
long long lazy[4 * N];

info ope(info u, info v) {
    return {u.num + v.num};
}

void build(const vector<int> &v, int in = 1, int L = 0, int R = n - 1) {
    if (L == R) {
        ST[in] = {v[L]};
    } else {
        int mid = (L + R) >> 1;

        build(v, 2 * in, L, mid);
        build(v, 2 * in + 1, mid + 1, R);

        ST[in] = ope(ST[2 * in], ST[2 * in + 1]);
    }
}

void push(int in, int L, int R) {
    if (lazy[in] == 0)
        return;

    ST[in].num += lazy[in] * (R - L + 1);

    if (L != R) {
        lazy[2 * in] += lazy[in];
        lazy[2 * in + 1] += lazy[in];
    }

    lazy[in] = 0;
}

void update(int l, int r, long long val,
            int in = 1, int L = 0, int R = n - 1) {

    push(in, L, R);

    if (r < L or R < l)
        return;

    if (l <= L and R <= r) {
        lazy[in] += val;
        push(in, L, R);
        return;
    }

    int mid = (L + R) >> 1;

    update(l, r, val, 2 * in, L, mid);
    update(l, r, val, 2 * in + 1, mid + 1, R);

    ST[in] = ope(ST[2 * in], ST[2 * in + 1]);
}

info get(int l, int r,
         int in = 1, int L = 0, int R = n - 1) {

    push(in, L, R);

    if (r < L or R < l)
        return {0};

    if (l <= L and R <= r)
        return ST[in];

    int mid = (L + R) >> 1;

    info left = get(l, r, 2 * in, L, mid);
    info right = get(l, r, 2 * in + 1, mid + 1, R);

    return ope(left, right);
}
