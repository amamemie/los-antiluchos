const int N = 1e5 + 10;
vector<int> path;
vector<int> G[N];
void EulerTour(int node, int parent){
    path.pb(node);
    for(int u : G[node]){
        if(u != parent){
            EulerTour(u,node);
        }
    }
    path.pb(node);
}

const int N = 1e5 + 10;
int tin[N];
int tout[N];
int flat[N];
int timer = 1;
void EulerTour(int node, int parent){
    tin[node] = timer;
    flat[timer] = node;
    timer++;
    for(int u : G[node]){
        if(u != parent){
            EulerTour(u, node);
        }
    }
    tout[node] = timer;
}
