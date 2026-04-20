const int N = 1e5;
struct info{
    int num;
};
info ST[4*N];
info ope(info u, info v){
    return {u.num+v.num};
}
void build(int in, int L, int R){
    if(L == R){
        cin >> ST[in].num;
    }
    else{
        int mid = (L+R)>>1;
        build((2*in),L,mid);
        build((2*in)+1,mid+1,R);
        ST[in] = ope(ST[(2*in)], ST[(2*in)+1]);
    }
}
void update(int in, int L, int R, int pos, int val){
    if(L == R){
        ST[in].num = val;
    }
    else{
        int mid = (L+R)>>1;
        if(pos <= mid){
            update(2*in,L,mid,pos,val);
        }
        else{
            update((2*in)+1,mid+1,R,pos,val);
        }
        ST[in] = ope(ST[2*in], ST[(2*in)+1]);
    }
}
info get(int in, int L, int R, int l, int r){
    if(r < L or R < l) return {0};
    if(l <= L and R <= r) return ST[in];
    int mid = (L+R)>>1;
    info left = get(2*in,L,mid,l,r);
    info right = get((2*in)+1,mid+1,R,l,r);
    return ope(left,right);
}
// v = {1 2 3 4 5}
// get(1, 0, n-1, 1, 3) = 2 + 3 + 4 = 9
