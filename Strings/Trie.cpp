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
