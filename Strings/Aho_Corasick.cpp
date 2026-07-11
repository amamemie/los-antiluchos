//AhoCorasick para saber si un string s existe en un texto T
const int E = 26;
const int N = 1e6+10;
int cur;
int nodoTerminal[N];//se guarda el nodo terminal del string i
set<int>st;//se guarda que nodos son terminales que aparecen en el texto T

struct AC {
    int nodes;
    vector<int>suf, super;
    vector<array<int, E>>go;
    vector<bool>terminal;
    AC(){
        add_node();
        nodes = 1;
    }
    void add_node(){
        terminal.emplace_back();
        go.emplace_back();
        super.emplace_back();
        suf.emplace_back();
    }

    void insert(string &s){
        int pos =  0;
        for(char ch : s){
            int c = ch - 'a';
            if(go[pos][c] == 0){
                go[pos][c] = nodes++;
                add_node();
            }
            pos = go[pos][c];
        }
        terminal[pos] =  true;
        nodoTerminal[cur] = pos;
    }

    void build(){
        queue<int>Q;
        Q.emplace(0);
        while(!Q.empty()){
            int u = Q.front();
            Q.pop();
            super[u] = (suf[u] == 0 or terminal[suf[u]] ? suf[u] : super[suf[u]]);
            for(int c = 0; c < E; c++){
                if(go[u][c]){
                    int v = go[u][c];
                    Q.emplace(v);
                    suf[v] = u == 0 ? 0 : go[suf[u]][c];
                }
                else{
                    go[u][c] = u == 0 ? 0 :go[suf[u]][c];
                }
            }
        }
    }
};

void mark(int u, AC &ac){
    if(u == 0) return;
    mark(ac.super[u], ac);
    if(ac.terminal[u]){
        st.insert(u);
        ac.terminal[u] = false;
    }
    ac.super[u] = 0;
}

void solve(){
    int n;
    cin >> n;
    AC ac;
    repl(i,0,n){
        string s;
        cin >> s;
        cur = i;
        ac.insert(s);
    }
    string t; //texto grande
    cin >> t;
    ac.build();
    int p = 0;
    for(auto x : t){
        int c = x - 'a';
        p = ac.go[p][c];
        mark(p, ac);
    }
    repl(i,0,n){
        if(st.count(nodoTerminal[i])){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}

//-------------------------------------------------------------------------

//AhoCorasick para Frecuencias
const int E = 26;
const int N = 1e6+10;
int nodoTerminal[N];
int cur;
struct AC {
    int nodes;
    vector<int>suf, freq, by_level;
    vector<bool>terminal;
    vector<array<int,E>>go;

    AC(){
        add_node();
        nodes = 1;
    }
    void add_node(){
        terminal.emplace_back();
        suf.emplace_back();
        go.emplace_back();
        freq.emplace_back();
    }

    void insert(string &s){
        int pos = 0;
        for(char ch:s){
            int c = ch - 'a';
            if(go[pos][c] == 0){
                go[pos][c] = nodes++;
                add_node();
            }
            pos = go[pos][c];
        }
        terminal[pos] = true;
        nodoTerminal[cur] = pos;
    }

    void build(){
        queue<int>Q;
        Q.emplace(0);
        while(!Q.empty()){
            int u = Q.front();
            Q.pop();
            by_level.emplace_back(u);
            for(int c = 0; c < E; c++){
                if(go[u][c]){
                    int v = go[u][c];
                    Q.emplace(v);
                    suf[v] = u == 0 ? 0 : go[suf[u]][c];
                }
                else{
                    go[u][c] = u == 0 ? 0 : go[suf[u]][c];
                }
            }
        }
    }
};

void solve(){
    int n;
    cin >> n;
    AC ac;
    repl(i,0,n){
        string s;
        cin >> s;
        cur = i;
        ac.insert(s);
    }
    string t;
    cin >> t;
    ac.build();
    int p = 0;
    for(char ch:t){
        int c = ch-'a';
        p = ac.go[p][c];
        ac.freq[p]++;
    }
    for(int i = (int)ac.by_level.size()-1; i > 0; i--){
        int x = ac.by_level[i];
        ac.freq[ac.suf[x]] += ac.freq[x];
    }
    repl(i,0,n){
        int termi = nodoTerminal[i];
        cout << ac.freq[termi] << '\n';
    }
}