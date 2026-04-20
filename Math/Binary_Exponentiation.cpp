const long long mod = 998244353;
long long pote(long long a, long long b){
    long long ans = 1ll;
    while(b){
        if(b&1) ans = (ans * a)%mod;
        b>>=1;
        a = (a * a)%mod;
    }
    return ans;
}
