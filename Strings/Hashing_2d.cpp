/*
    2D Hashing: buscar todas las apariciones de una matriz
    r x c dentro de una matriz n x m.
*/

const ll BASE = 911382323LL;

void solve() {
    int r, c;
    cin >> r >> c;

    vector<string> pattern(r);
    for (int i = 0; i < r; i++)
        cin >> pattern[i];

    // Potencias para el rolling vertical.
    vector<ll> power(r + 1, 1);
    for (int i = 1; i <= r; i++)
        power[i] = power[i - 1] * BASE;

    // Hash de la matriz patrón.
    ll patternHash = 0;

    for (int i = 0; i < r; i++) {
        Hash h(pattern[i]);
        ll rowHash = h.get(0, c);

        patternHash += rowHash * power[r - i - 1];
    }

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        cin >> grid[i];

    // rowHash[i][j] = hash de grid[i][j ... j+c-1].
    vector<vector<ll>> rowHash(
        n, vector<ll>(m - c + 1)
    );

    for (int i = 0; i < n; i++) {
        Hash h(grid[i]);

        for (int j = 0; j <= m - c; j++)
            rowHash[i][j] = h.get(j, j + c);
    }

    // matrixHash[i][j] = hash de la submatriz r x c desde (i,j).
    vector<vector<ll>> matrixHash(
        n - r + 1,
        vector<ll>(m - c + 1)
    );

    for (int j = 0; j <= m - c; j++) {
        ll cur = 0;

        // Primera ventana vertical.
        for (int i = 0; i < r; i++)
            cur += rowHash[i][j] * power[r - i - 1];

        matrixHash[0][j] = cur;

        // Rolling vertical.
        for (int i = 1; i <= n - r; i++) {
            cur -= rowHash[i - 1][j] * power[r - 1];
            cur = cur * BASE + rowHash[i + r - 1][j];

            matrixHash[i][j] = cur;
        }
    }

    // 2D difference array para marcar las apariciones.
    vector<vector<int>> diff(
        n + 1, vector<int>(m + 1, 0)
    );

    for (int i = 0; i <= n - r; i++) {
        for (int j = 0; j <= m - c; j++) {

            if (matrixHash[i][j] == patternHash) {
                diff[i][j]++;
                diff[i][j + c]--;
                diff[i + r][j]--;
                diff[i + r][j + c]++;
            }
        }
    }

    // Prefijos 2D.
    for (int i = 0; i < n; i++)
        for (int j = 1; j < m; j++)
            diff[i][j] += diff[i][j - 1];

    for (int j = 0; j < m; j++)
        for (int i = 1; i < n; i++)
            diff[i][j] += diff[i - 1][j];

    // Imprimir celdas pertenecientes a alguna aparición.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << (diff[i][j] > 0 ? grid[i][j] : '.');
        }
        cout << '\n';
    }
}