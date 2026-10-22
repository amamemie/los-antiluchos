#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Merge Sort Tree
// Cada nodo guarda el segmento [l, r] del arreglo ORDENADO.
//
// Construccion: O(n log n) tiempo y memoria
// Consultas   : O(log^2 n)   (log n nodos * busqueda binaria)
//
// Sirve para (sin updates):
//   - cuantos elementos < x (o <= x) en [l, r]
//   - cuantos elementos en rango de valores [lo, hi] dentro de [l, r]
//   - k-esimo menor en [l, r]  (busqueda binaria sobre el valor)
//
// Indices 0-based, consultas con [l, r] inclusivo.
// ============================================================
struct MergeSortTree {
    int n;
    vector<vector<int>> t;  // t[nodo] = elementos del segmento, ordenados

    MergeSortTree() {}
    MergeSortTree(const vector<int>& a) { build(a); }

    void build(const vector<int>& a) {
        n = a.size();
        t.assign(4 * n, {});
        build(1, 0, n - 1, a);
    }

    void build(int node, int l, int r, const vector<int>& a) {
        if (l == r) {                 // hoja: un solo elemento
            t[node] = {a[l]};
            return;
        }
        int m = (l + r) / 2;
        build(2 * node, l, m, a);
        build(2 * node + 1, m + 1, r, a);
        // mezclar los dos hijos ya ordenados (como en merge sort)
        t[node].resize(r - l + 1);
        merge(t[2 * node].begin(), t[2 * node].end(),
              t[2 * node + 1].begin(), t[2 * node + 1].end(),
              t[node].begin());
    }

    // cantidad de elementos < x en [ql, qr]
    int count_less(int ql, int qr, int x) { return count_less(1, 0, n - 1, ql, qr, x); }

    int count_less(int node, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql) return 0;          // fuera del rango
        if (ql <= l && r <= qr)                  // totalmente dentro: busqueda binaria
            return lower_bound(t[node].begin(), t[node].end(), x) - t[node].begin();
        int m = (l + r) / 2;
        return count_less(2 * node, l, m, ql, qr, x) +
               count_less(2 * node + 1, m + 1, r, ql, qr, x);
    }

    // cantidad de elementos <= x en [ql, qr]
    int count_leq(int ql, int qr, int x) { return count_less(ql, qr, x + 1); }  // solo enteros

    // cantidad de elementos con valor en [lo, hi] dentro de [ql, qr]
    int count_range(int ql, int qr, int lo, int hi) {
        return count_leq(ql, qr, hi) - count_less(ql, qr, lo);
    }

    // k-esimo menor (k = 1 es el minimo) en [ql, qr]
    // busqueda binaria sobre el valor: O(log(MAXV) * log^2 n)
    int kth(int ql, int qr, int k, int lo = -1e9, int hi = 1e9) {
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;       // piso seguro para negativos
            if (count_leq(ql, qr, mid) >= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

// ---------------- Ejemplo de uso ----------------
// int main() {
//     vector<int> a = {5, 1, 4, 2, 3};
//     MergeSortTree mst(a);
//     cout << mst.count_less(0, 4, 4) << "\n";       // 3  (1, 2, 3)
//     cout << mst.count_range(1, 3, 2, 4) << "\n";   // 2  (4, 2)
//     cout << mst.kth(0, 4, 2) << "\n";              // 2
// }
