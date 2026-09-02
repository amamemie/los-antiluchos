int n;
vector<vector<int>> G;
vector<int> mt;
vector<bool> used;
bool try_kuhn(int v){
    if(used[v]) return false;
    used[v] = true;
    for(int to : G[v]){
        if(mt[to] == -1 or try_kuhn(mt[to])){
            mt[to] = v;
            return true;
        }
    }
    return false;
}
void solve(int tc){
    mt.assign(n, -1);
    repl(v,0,n){
        used.assign(n, false);
        try_kuhn(v);
    }
}
