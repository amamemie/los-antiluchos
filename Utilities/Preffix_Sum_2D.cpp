//1 indexed
const int N = 1005;
int v[N][N];
int acu[N][N];
int n, m;

void solve() {
    //limpiar la acu para cada TC

    // Construccion: acumula 1 si el elemento es exactamente 1
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int val = (v[i][j] == 1 ? 1 : 0);
            acu[i][j] = val + acu[i - 1][j] + acu[i][j - 1] - acu[i - 1][j - 1];
        }
    }

    // Esquinas de consulta:
    // (a, b) -> Superior Izquierda
    // (c, d) -> Inferior Derecha
    int a = 2, b = 2, c = 4, d = 4; // Valores de ejemplo

    int ans = acu[c][d] - acu[a - 1][d] - acu[c][b - 1] + acu[a - 1][b - 1];
    cout << ans << '\n';
}