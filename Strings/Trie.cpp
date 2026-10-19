const int E = 26;

struct AC {
    int nodes;
    vector<array<int, E>>go;
    vector<bool>terminal;

    AC(){
        add_node();
        nodes = 1;
    }

    void add_node(){
        terminal.emplace_back();
        go.emplace_back();
    }

    void insert(string &s){
        int pos =  0;
        for(char ch : s){
            int c = ch - '0';
            if(go[pos][c] == 0){
                go[pos][c] = nodes++;
                add_node();
            }
            pos = go[pos][c];
        }
        terminal[pos] =  true;
    }
    
};
//TRIE XOR
struct Trie{
    int nodes;
    vector<array<int,E>> go;
    vector<int> can;
    Trie(){
        add_node();
        nodes = 1;
    }
    void add_node(){
        go.push_back({-1,-1});
        can.emplace_back();
    }
    void insert(int x){
        int pos = 0;
        can[pos]++;
        for(int i = 29; i >= 0; i--){
            int bit = ((x >> i) & 1);
            if(go[pos][bit] == -1){
                add_node();
                go[pos][bit] = nodes++;
            }
            pos = go[pos][bit];
            can[pos]++;
        }
    }
    void erase(int x){
        int pos = 0;
        can[pos]--;
        for(int i = 29; i >= 0; i--){
            int bit = ((x >> i) & 1);
            int next = go[pos][bit];
            can[next]--;
            if(can[next] == 0) go[pos][bit] = -1;
            pos = next;
        }
    }
    int get(int x, int k){
        int val = 0;
        int pos = 0;
        for(int i = 29; i >= 0; i--){
            int b = (x >> i) & 1;
            int nxt = go[pos][b];
            if(nxt != -1 and can[nxt] >= k){
                pos = nxt;
                val += (1 << i) * b;
            }
            else{
                if(nxt != -1) k -= can[nxt];
                pos = go[pos][b ^ 1];
                val += (1 << i) * (b ^ 1);
            }
        }
        return val ^ x;
    }
};
