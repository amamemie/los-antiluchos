vector<int> suffix_array(string s) {
    s += char(0);
    const int n = s.size();
    vector<int>a(n);
    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&] (int i, int j){
        return s[i] < s[j];
    });
    vector<int> mapping(n);
    mapping[a[0]] = 0;
    for(int i = 1; i < n; i++){
        mapping[a[i]] = mapping[a[i-1]]+(s[a[i-1]] != s[a[i]]);
    }
    int len = 1;
    vector<int>sbs(n);
    vector<int>head(n);
    vector<int>new_mapping(n);
    while(len < n){
        for(int i = 0; i<n; i++) sbs[i] = (a[i] + n - len) % n;
        for(int i = n-1; i>=0; i--) head[mapping[a[i]]] = i;
        for(int i = 0; i < n; i++){
            int x = sbs[i];
            a[head[mapping[x]]++] = x;
        }
        new_mapping[a[0]] = 0;
        for(int i = 1; i < n; i++){
            if(mapping[a[i-1]] != mapping[a[i]]){
                new_mapping[a[i]] = new_mapping[a[i-1]]+1;
            }
            else{
                int pre = mapping[(a[i-1] + len)%n];
                int cur = mapping[(a[i]+len) % n];
                new_mapping[a[i]] = new_mapping[a[i-1]] + (pre!=cur);
            }
        }
        len <<= 1;
        swap(mapping, new_mapping);
    }
    return vector<int>(a.begin()+1, a.end());//ignorar a[0] que es el centinela
}

vector<int> lcp_array(vector<int>&a, string s){
    const int n = s.size();
    vector<int> rank(n);
    for(int i = 0; i < n; i++) rank[a[i]] = i;
    int k = 0;
    vector<int>lcp(n);
    for(int i = 0; i < n; i++){
        if(rank[i] == n-1){
            k = 0;
            continue;
        }
        int j = a[rank[i]+1];
        while(i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
    lcp.pop_back();
    return lcp;
}

void solve(){
    //Numero de distintos substr en un string n*(n+1)/2 - sumatoria del LCP
    //verificar si un string es substring de otro con BS en SA
    //encontrar el longest common substring en 2 strings(ESTA IMPLEMENTACION)
    string s, t;
    cin >> s >> t;
    if(s.size() > t.size()){
        swap(s, t);
    }
    int n = s.size();
    int m = t.size();
    string st = s+'#'+t;
    vector<int>sa = suffix_array(st);
    vector<int>lcp =lcp_array(sa, st);
    // print(sa);
    // print(lcp);
    vector<int>tr(n+m);
    repl(i,0,n+m){
        if(sa[i] >=n and sa[i+1]>=n){
            tr[i] = 0;
            continue;
        }
        if(sa[i] < n and sa[i+1] < n){
            tr[i] = 0;
            continue;
        }
        int mn = min(sa[i], sa[i+1]);
        int tam1 = mn + lcp[i];
        // dbg(tam1);
        tr[i] = lcp[i];
        if(tam1 > n){
            dbg(tam1);
            tr[i] = lcp[i] - (tam1-n);
        }
    }   
    // print(tr);
    int mx = *max_element(tr.begin(), tr.end());
    repl(i,0,n+m){
        // dbg(tr[i]);
        if(tr[i] == mx){
            string ans = st.substr(sa[i], mx);
            cout << ans << '\n';
            return;
        }
    }
    
}
//Sabrossus