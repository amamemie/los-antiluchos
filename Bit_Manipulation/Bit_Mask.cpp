for(int mask = 0; mask < (1 << n); mask++) { //(1 << n) = O(2^n)
    for(int i = 0; i < n; i++) { // O(n)
    //verificamos si el i-esimo bit esta encendido
        if(mask & (1 << i)) {
            cout << v[i] << " ";
        }
    }
}
