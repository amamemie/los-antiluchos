struct LB {
    int b[30] = {}, sz = 0;
    bool zero = 0; // Indica si se puede formar el 0

    // 1. Inserta un número en la base
    void insert(int mask) {
        for (int i = 29; i >= 0; i--) {
            if ((mask >> i) & 1) {
                if (!b[i]) { b[i] = mask; sz++; return; }
                mask ^= b[i];
            }
        }
        zero = 1; 
    }

    // 2. Comprueba si un valor específico se puede formar usando XOR
    bool query(int mask) {
        for (int i = 29; i >= 0; i--) {
            if ((mask >> i) & 1) {
                if (!b[i]) return 0;
                mask ^= b[i];
            }
        }
        return 1;
    }

    // 3. Maximiza un valor haciendo XOR con elementos de la base
    int maximize(int val) {
        for (int i = 29; i >= 0; i--) if ((val ^ b[i]) > val) val ^= b[i];
        return val;
    }

    // 4. Minimiza un valor haciendo XOR con elementos de la base
    int minimize(int val) {
        for (int i = 29; i >= 0; i--) if ((val ^ b[i]) < val) val ^= b[i];
        return val;
    }

    // 5. Retorna la cantidad total de valores únicos distintos (2^sz)
    long long count_distinct() {
        return 1LL << sz;
    }

    // 6. Obtiene el k-ésimo valor más pequeño que se puede formar (0-indexed)
    int get_kth(long long k) {
        vector<int> active;
        for (int i = 0; i < 30; i++) if (b[i]) active.push_back(b[i]);
        if (k >= (1LL << active.size())) return -1;
        int res = 0;
        for (size_t i = 0; i < active.size(); i++) {
            if ((k >> i) & 1) res ^= active[i];
        }
        return res;
    }

    // 7. Fusiona otra base linear en esta
    void merge(const LB& other) {
        for (int i = 0; i < 30; i++) if (other.b[i]) insert(other.b[i]);
    }
};
