const int N = 1e5;
const int LOG = 20;
int v[N]; //values
int st[N][LOG]; //Sparse Table
int lg[N]; // log values
int n;
void build(){
    for(int i = 0; i < n; i++) st[i][0] = v[i];

    for(int i = 1; i < LOG; i++){
        for(int j = 0; j < n - (1<<i) + 1; j++){
            st[j][i] = min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
        }
    }
    lg[1] = 0;
    for(int i = 2; i <= n;i++) lg[i] = lg[i/2] + 1;
}
int query(int L, int R){
    int k = lg[R-L+1];
    return min(st[L][k],st[R-(1<<k)+1][k]);
}
// v = [5, 2, 4, 7, 1, 3]
// query(1, 4) → [2, 4, 7, 1]
