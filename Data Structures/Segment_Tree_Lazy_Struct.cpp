// CSES Range Update and Sums
// q = 1 sumar x a todo un rango
// q = 2 todos los valores en un rango deben ser igual a x

const int N = 2e5+10;
 
int n;
 
struct info{
    ll sum, estado, lazy;
};
info ST[4*N];
 
info ope(info a, info b){
    info aux;
    aux.lazy = 0;
    aux.estado = 0;
    aux.sum = a.sum + b.sum;
    return aux;
}
 
void build(const vector<ll> &v, int in = 1, int L = 0, int R = n-1){
    if(L == R){
        ST[in] = {v[L], 0 , 0};
        return;
    }
    int mid = (R+L)/2;
    build(v, 2*in, L, mid);
    build(v, 2*in+1, mid+1, R);
    ST[in] = ope (ST[2*in], ST[2*in+1]);;
}
 
void push(int in, int L, int R){
 
    if(ST[in].estado == 0){
        return;
    }
 
    if(ST[in].estado == 1){
        ST[in].sum += ST[in].lazy * (R - L + 1);
        if(L != R){
            ST[2*in].lazy += ST[in].lazy;
            ST[2*in+1].lazy += ST[in].lazy;
            if(ST[2*in].estado == 0){
                ST[2*in].estado = ST[in].estado;
            }
            if(ST[2*in+1].estado == 0){
                ST[2*in+1].estado = ST[in].estado;
            }
        }
    }
    else{
        ST[in].sum = ST[in].lazy * (R - L + 1);
        if(L != R){
            ST[2*in].lazy = ST[in].lazy;
            ST[2*in+1].lazy = ST[in].lazy;
            ST[2*in].estado = ST[in].estado;
            ST[2*in+1].estado = ST[in].estado;
        }
    }
    ST[in].estado = 0;
    ST[in].lazy = 0;
}
 
void update(int l, int r, ll val, ll estado, int in = 1, int L = 0, int R = n-1){
    push(in, L, R);
    if(r < L or R < l){
        return ;
    }
    if(l <= L and R <= r){
        ST[in].estado = estado;
        if(estado == 1){
            ST[in].lazy += val;
            push(in, L, R);
        }
        else{
            ST[in].lazy = val;
            push(in, L, R);
        }
        return;
    }
 
    int mid = (R+L)/2;
    update(l, r, val, estado, 2*in, L, mid);
    update(l, r, val, estado, 2*in+1, mid+1, R);
    ST[in] = ope(ST[2*in], ST[2*in+1]);
}
 
info query(int l, int r, int in = 1, int L = 0, int R = n-1){
    push(in, L, R);
    if(r < L or R < l){
        return {0, 0 ,0};
    }
 
    if(l <= L and R <= r){
        return ST[in];
    }
 
    int mid = (R+L)/2;
    info left = query(l, r, 2*in, L, mid);
    info right = query(l, r, 2*in+1, mid+1, R);
    return ope(left, right);
}
 
 
void solve(){
    int Q;
    cin >> n >> Q;
    vector<ll>v(n);
    repl(i,0,n){
        cin >> v[i];
    }
    build(v);
    while(Q--){
        int q;
        cin >> q;
        // dbg(q);
        if(q==1 or q==2){
            int l, r;
            cin >> l >> r;
            ll x;
            l--, r--;
            cin >> x;
            update(l, r, x, q);
        }
        else{
            int l, r;
            cin >> l >> r;
            l--, r--;
            ll ans = query(l, r).sum;
            cout << ans << "\n";
        }
    }
 
}
