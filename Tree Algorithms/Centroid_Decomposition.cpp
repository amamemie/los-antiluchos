//EJERCICIO IMPLEMENTACION XENIA AND TREE
//Nodo rojo mas cercano a un nodo v

const int N = 2e5+10;
vector<int>G[N];
int tag[N]; // time of discovery of centrodi
int fat[N]; // father in centroid decomposition
int szt[N]; // size of subtree

int best[N];
int niv[N];
int dist[30][N]; //dist[nivel][nodo];

void dfs_level(int node, int p, int niv, int prof){
    dist[niv][node] = prof;
    for(auto y : G[node]){
        if(y != p and tag[y] < 0){
            dfs_level(y, node, niv, prof+1);
        }
    }
}
// -----------------CENTROID-------------------------
int calcsz(int node, int p){
    szt[node] = 1;
    for(auto y : G[node]){
        if(y != p and tag[y] < 0){
            szt[node] += calcsz(y, node);
        }
    }
    return szt[node];
}
int ccnt = 0;
void cdfs(int node, int p, int nivel = 0, int sz = -1){
    if(sz < 0) sz = calcsz(node, -1);
    for(auto y : G[node]){
        if(tag[y] < 0 and szt[y] * 2 >= sz){
            szt[node] = 0;
            cdfs(y, p, nivel, sz);
            return;
        }
    }
    tag[node] = ccnt++;
    fat[node] = p;
    niv[node] = nivel;
    dfs_level(node, -1, nivel, 0);
    for(auto y : G[node]){
        if(tag[y] < 0){
            cdfs(y, node, nivel+1);
        }
    }
}

int n;
void centroid(){
    ccnt = 0;
    repl(i,1,n+1){
        tag[i] = -1;
    }
    cdfs(1, -1);
}

//---------------------------------------------

void update(int node, int rojo){
    int nivel = niv[node];
    int cost = dist[nivel][rojo];   
    best[node] = min(best[node], cost);
    int p = fat[node];
    if(p > 0){
        update(p, rojo);
    }
}

int improve(int node, int cur){
    if(node <= 0){
        return 1e9;
    }
    int nivel = niv[node];
    int cost = best[node] + dist[nivel][cur];
    int p = fat[node];
    return min(cost, improve(p, cur));
}

void solve(){
    int qq;
    cin >> n >> qq;
    repl(i,0,30){
        repl(j,1,n+1){
            dist[i][j] = -1;
            best[j] = 1e9;
        }
    }
    repl(i,0,n-1){
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    centroid();
    update(1, 1);
    while(qq--){
        int q, node;
        cin >> q >> node;
        if(q == 1){
            update(node, node);
        }   
        else{
            int res = best[node];
            int res2 = improve(node, node);
            cout << min(res, res2) << '\n';
        }
    }
}
 
int main(){
    velocito;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
//Sabrossus
//TC Argentina