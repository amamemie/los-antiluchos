const int N = 1e5;

struct info {
    int num;
};

info ST[4 * N];

info ope(info u, info v) {
    return {u.num + v.num};
}

void build(const vector<int> &v, int in = 1, int L = 0, int R = n - 1) {
    if (L == R) {
        ST[in] = {v[L]}; // Asignamos el valor desde el vector
    } else {
        int mid = (L + R) >> 1;
        build(v, 2 * in, L, mid);
        build(v, (2 * in) + 1, mid + 1, R);
        ST[in] = ope(ST[2 * in], ST[(2 * in) + 1]);
    }
}

void update(int pos, int val, int in = 1, int L = 0, int R = n - 1) {
    if (L == R) {
        ST[in].num = val;
    } else {
        int mid = (L + R) >> 1;
        if (pos <= mid) {
            update(pos, val, 2 * in, L, mid);
        } else {
            update(pos, val, (2 * in) + 1, mid + 1, R);
        }
        ST[in] = ope(ST[2 * in], ST[(2 * in) + 1]);
    }
}

info get(int l, int r, int in = 1, int L = 0, int R = n - 1) {
    if (r < L or R < l) return {0}; // Elemento neutro
    if (l <= L and R <= r) return ST[in];
    
    int mid = (L + R) >> 1;
    info left = get(l, r, 2 * in, L, mid);
    info right = get(l, r, (2 * in) + 1, mid + 1, R);
    return ope(left, right);
}


// Llamadas simples y limpias:
// build(v);             // Construye con el vector
// update(2, 10);        // Cambia el valor en pos 2 a 10
// info ans = get(1, 3); // Obtiene la respuesta en el rango [1, 3]
// v = {1 2 3 4 5}
// get(1, 0, n-1, 1, 3) = 2 + 3 + 4 = 9
