int n;
cin >> n;
vector < vector < int >> v(n);
repl(i, 0, n) {
    repl(j, 0, n) {
        int x;
        cin >> x;
        v[i].push_back(x);
    }
}
int maxi = INT_MIN;
repl(ini, 0, n) {
    vector < int > pref(n, 0);
    repl(i, ini, n) {
        repl(j, 0, n) {
            pref[j] += v[i][j];
        }
        int cur = 0;
        repl(j, 0, n) {
            cur = max(pref[j], pref[j] + cur);
            maxi = max(maxi, cur);
        }
    }
}
