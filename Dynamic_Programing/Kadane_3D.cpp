int n;
cin >> n;

repl(i, 0, n) {
    repl(j, 0, n) {
        repl(k, 0, n) {
            cin >> v[i][j][k];
        }
    }
}
int maxi = INT_MIN;
repl(k_ini, 0, n) {
    vector < vector < int >> pref2(n, vector < int > (n, 0));
    repl(k, k_ini, n) {
        repl(i, 0, n) {
            repl(j, 0, n) {
                pref2[i][j] += v[i][j][k];
            }
        }
        repl(ini, 0, n) {
            vector < int > pref(n, 0);
            repl(i, ini, n) {
                repl(j, 0, n) {
                    pref[j] += pref2[i][j];
                }
                int cur = 0;
                repl(u, 0, n) {
                    cur = max(pref[u], cur + pref[u]);
                    maxi = max(maxi, cur);
                }
            }

        }
    }
}

cout << maxi << "\n";
