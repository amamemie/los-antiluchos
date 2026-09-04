struct info
{
    int num;
};

int sz;
vector<info> ST;

void build(int n) {
    sz = 1;
    while (sz < n) sz *= 2;
    ST.assign(2 * sz, {1000000000});
}

void update(int pos, int val) {
    pos += sz;
    ST[pos].num = min(ST[pos].num, val);
    for (pos /= 2; pos > 0; pos /= 2) {
        ST[pos].num = min(ST[2 * pos].num, ST[2 * pos + 1].num);
    }
}

info get(int l, int r) {
    int res = 1000000000;
    for (l += sz, r += sz + 1; l < r; l /= 2, r /= 2) {
        if (l & 1) res = min(res, ST[l++].num);
        if (r & 1) res = min(res, ST[--r].num);
    }
    return {res};
}
//Consultas exactamente igual que el recursivo
