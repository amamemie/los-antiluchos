void solve(){
    string s, p;
    cin >> s >> p;
    int n = s.size();
    int m = p.size();
    vector<int> ans(n - m + 1);
    for(char c = 'A'; c <= 'Z'; c++){
        vector<int> a(n);
        vector<int> b(m);
        for(int i = 0; i < n; i++)
            if(s[i] == c)
                a[i] = 1;
        for(int i = 0; i < m; i++)
            if(p[i] == c)
                b[m - 1 - i] = 1;
        vector<int> cur = multiply(a, b);
        for(int i = 0; i < n - m + 1; i++)
            ans[i] += cur[i + m - 1];
    }
    for(int i = 0; i < n - m + 1; i++){
        if(ans[i] == m)
            cout << i << ' ';
    }
    cout << '\n';
}
