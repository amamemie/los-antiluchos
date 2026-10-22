const ll N = 2e6 + 10;
ll n;
struct info{
    ll mn, cnt;
};
info ST[4 * N];
ll lazy[4 * N];
info ope(info u, info v){
    if(u.mn < v.mn) return u;
    if(v.mn < u.mn) return v;
    return {u.mn, u.cnt + v.cnt};
}
void build(ll in = 1, ll L = 0, ll R = n - 1){
    lazy[in] = 0;
    if(L == R){
        ST[in] = {0,1};
    }
    else{
        ll mid = (L + R) / 2;
        build(2 * in, L, mid);
        build(2 * in + 1, mid + 1, R);
        ST[in] = ope(ST[2 * in], ST[2 *in + 1]);
    }
}
void push(ll in, ll L, ll R){
    if(lazy[in] == 0){
        return;
    }
    ST[in].mn += lazy[in];

    if(L != R){
        lazy[2 * in] += lazy[in];
        lazy[2 * in + 1] += lazy[in];
    }
    lazy[in] = 0;
}
void update(ll l, ll r, ll val, ll in = 1, ll L = 0, ll R = n - 1){
    push(in, L, R);
    if(r < L or R < l){
        return;
    }
    if(l <= L and R <= r){
        lazy[in] += val;
        push(in, L, R);
        return;
    }
    ll mid = (L + R) / 2;
    update(l, r, val, 2 * in, L, mid);
    update(l, r, val, 2 * in + 1, mid + 1, R);
    ST[in] = ope(ST[2 * in], ST[2 * in + 1]);
}
info get(ll l, ll r, ll in = 1, ll L = 0, ll R = n - 1){
    push(in, L, R);
    if(r < L or R < l){
        return {INT_MAX, 0};
    }
    if(l <= L and R <= r){
        return ST[in];
    }
    ll mid = (L + R) / 2;
    info left = get(l, r, 2 * in, L, mid);
    info right = get(l, r, 2 * in + 1, mid + 1, R);
    return ope(left, right);
}
void solve(){
    ll m; cin >> m;
    vector<array<ll,4>> v;
    repl(i,0,m){
        ll x1,y1,x2,y2; 
        cin >> x1 >> y1 >> x2 >> y2; 
        v.push_back({x1,y1,y2,1});
        v.push_back({x2,y1,y2,0});
    }
    n = 2e6 + 10;
    build();
    sort(v.begin(),v.end());
    ll last = v[0][0];
    ll ans = 0ll;
    ll off = 1e6;
    repl(i,0,v.size()){
        info q = get(0,n-1);
        ll total = n;
        if(q.mn == 0){
            total = n - q.cnt;
        }
        ll base = v[i][0] - last;
        ans += (total * base);
        last = v[i][0];
        if(v[i][3] == 1){
            update(off + v[i][1], off + v[i][2]-1, 1);
        }
        else{
            update(off + v[i][1], off + v[i][2]-1, -1);
        }
        
    }
    cout << ans << "\n";
}
