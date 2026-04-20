long long pote(long long a, long long b, long long mod){
    long long ans = 1ll;
    while(b){
        if(b&1) ans = (ans * a)%mod;
        a = (a * a)%mod;
        b>>=1;
    }
    return ans;
}
