struct BIT_2D{
    vector<vector<int>> bit;
    int n,m;

    BIT_2D(int x, int y){
        bit.assign(x+1,vector<int> (y+1,0));
        n = x;
        m = y;
    }

    void update(int x, int y, int val){
        for(int i = x ; i <= n ; i+=i&(-i)){
            for(int j= y; j <=m ; j+=j&(-j)){
                bit[i][j] += val;
            }
        }
    }

    int sum(int x, int y){
        int ans = 0;
        for(int i = x ; i >0 ; i-=i&-i){
            for(int j= y; j >0 ; j-=j&-j){
                ans += bit[i][j];
            }
        }
        return ans;
    }

    int query(int x1, int y1, int x2, int y2){
        return sum(x2,y2) + sum(x1-1,y1-1) - sum(x1-1,y2) - sum(x2,y1-1);
    }
};

void solve(){
    int n,q;
    cin >> n >> q;
    BIT_2D bit(n,n);
    vector<vector<int>> mt(n+1,vector<int>(n+1,0));
    for(int i = 1 ;i  <= n; i ++){
        for(int j = 1 ; j <= n ;j++){
            char uwu;
            cin >> uwu;
            if(uwu=='.') continue;
            mt[i][j] = 1;
            bit.update(i,j,1);
        }
    }
    while(q--){
        int tipo;
        cin >> tipo;
        if(tipo == 1){
            int x,y;
            cin >> x >> y;
            if(mt[x][y]){
                bit.update(x,y,-1);
            }
            else{
                bit.update(x,y,1);
            }
            mt[x][y] ^= 1;
        }
        else{
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >>y2;
            cout << bit.query(x1,y1,x2,y2) << '\n';
        }
    }
}
//No entiendo w, el dildan lo hizo