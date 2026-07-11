// Rango de uso: 0-indexed. 
// Llamar en el solve como: mergeSort(v, 0, n - 1);
ll ans = 0; 

void mergeSort(vector<ll> &v, int low, int high) {
    if (low == high) return;

    int mid = (low + high) >> 1;
    mergeSort(v, low, mid);
    mergeSort(v, mid + 1, high);

    queue<ll> L, H;
    for (int i = low; i < mid + 1; i++) {
        L.push(v[i]);
    }
    for (int i = mid + 1; i < high + 1; i++) {
        H.push(v[i]);
    }

    for (int i = low; i < high + 1; i++) {
        if (L.size() == 0) {
            v[i] = H.front();
            H.pop();
        } 
        else if (H.size() == 0) {
            v[i] = L.front();
            L.pop();
        } 
        else {
            if (L.front() <= H.front()) {
                v[i] = L.front();
                L.pop();
            } 
            else {
                v[i] = H.front();
                H.pop();
                ans += L.size(); // Inversion detectada
            }
        }
    }
}