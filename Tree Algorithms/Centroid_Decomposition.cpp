const int N = 1e5;
vector<int> G[N];
int tag[N]; // time of discovery of centroid
int fat[N]; // father in centroid decomposition
int szt[N]; // size of subtree
int calcsz(int node, int parent){
    szt[node] = 1;
    for(auto u : G[node]){
        if(u != parent and tag[u] < 0){
            szt[node] += calcsz(u, node);
        }
    }
    return szt[node];
}
int ccnt = 0;
void cdfs(int node, int parent, int sz = -1){ // O(nlogn)
    if(sz < 0) sz = calcsz(node, -1);
    for(auto y : G[node]){
        if(tag[y] < 0 && szt[y] * 2 >= sz){
            szt[node] = 0; cdfs(y, parent, sz); return;
        }
    }
    tag[node] = ccnt++; fat[node] = parent;
    for(auto y : G[node]) if(tag[y] < 0) cdfs(y, node);
}
void centroid(){
    for(int i = 0; i < N; i++) tag[i] = -1;
    ccnt = 0;
    cdfs(1, -1);
}
