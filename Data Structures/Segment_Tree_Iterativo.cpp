struct info
{
    int num;
};

info ope(info u, info v){
    return {min(u.num, v.num)};
}

int sz;
vector<info> ST;

void build(int n) {
    sz = 1;
    while (sz < n) sz *= 2;
    ST.assign(2 * sz, {1000000000});
}

void update(int pos, int val) {
    pos += sz;
    ST[pos] = ope(ST[pos], {val});
    for (pos /= 2; pos > 0; pos /= 2) {
        ST[pos] = ope(ST[2 * pos], ST[2 * pos + 1]);
    }
}

info get(int l, int r) {
    info res = {1000000000};
    for (l += sz, r += sz + 1; l < r; l /= 2, r /= 2) {
        if (l & 1) res = ope(res, ST[l++]);
        if (r & 1) res = ope(res, ST[--r]);
    }
    return res;
}
//Las operaciones y consultas son iguales al recursivo, 0-index
