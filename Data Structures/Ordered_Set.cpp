#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    ordered_set st;

    st.insert(10);
    st.insert(30);
    st.insert(20);

    // 1. Elemento en la posicion K (0-indexed, de menor a mayor)
    // find_by_order devuelve un iterador (puntero). Usamos '*' para el valor.
    auto it = st.find_by_order(1); 
    if (it != st.end()) {
        int elemento = *it; // Devuelve 20 de forma segura
    }
    
    // 2. Cuantos elementos son estrictamente menores que X
    int menores_que_25 = st.order_of_key(25); // Devuelve 2 (el 10 y el 20)
}
// Sabrossus