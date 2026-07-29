// --- LECTURA BÁSICA ---
__int128 read128() {
    string s;
    cin >> s;
    __int128 n = 0;
    int sign = 1;
    size_t start = 0;

    if (!s.empty() && s[0] == '-') {
        sign = -1;
        start = 1;
    }

    for (size_t i = start; i < s.length(); ++i) {
        n = n * 10 + (s[i] - '0');
    }

    return n * sign;
}

// --- IMPRESIÓN BÁSICA ---
void print128(__int128 n) {
    if (n == 0) {
        cout << 0;
        return;
    }
    if (n < 0) {
        cout << '-';
        n = -n;
    }
    string s;
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}