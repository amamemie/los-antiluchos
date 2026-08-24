vector<int> z_function(string s){
    int n = s.size();
    vector<int> z(n,0);
    int l = 0;
    int r = 0;
    repl(i,1,n){
        if(i < r){
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n and s[z[i]] == s[i + z[i]]){
            z[i]++;
        }
        if(i + z[i] > r){
            l = i; 
            r = i + z[i];
        }
    }
    return z;
}
