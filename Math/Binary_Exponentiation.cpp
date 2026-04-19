const ll mod = 998244353;
ll pote(ll a, ll b){
    ll ans = 1ll;
    while(b){
        if(b&1) ans = (ans * a)%mod;
        b>>=1;
        a = (a * a)%mod;
    }
    return ans;
}
