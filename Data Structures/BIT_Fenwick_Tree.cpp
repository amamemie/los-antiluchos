struct BIT{
    int n;
    vector<int> bit;

    BIT(int _n){
        n =_n;
        bit.assign(n+1,0);
    }

    void add(int i, int val){
        while(i<=n){
            bit[i] += val;
            i += (i&(-i));
        }
    }

    int sum(int i){
        int ans = 0;
        while(i > 0){
            ans += bit[i];
            i -= (i&(-i));
        }
        return ans;
    }

    int query(int l, int r){
        return sum(r) - sum(l-1);
    }
};
//se debe utilizar con index 1
//Sabrossus