string tobit(long long x) {
    string a(64, '0'); 
    for (int i = 63; i >= 0; --i) {
        if (x & 1) a[i] = '1';
        x >>= 1;
    }
    return a;
}
