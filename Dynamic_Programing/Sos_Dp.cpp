void sos_dp(vector<ll>& dp, int K){
//  k es el tamanho del arreglo :v
    for(int bit = 0; bit < K; bit++){
        for(int mask = 0; mask < (1 << K); mask++){
            if(mask & (1 << bit)){
                dp[mask] += dp[mask ^ (1 << bit)];
//		si quieres que sea un sos dp de maximos
//		dp[mask] = max(dp[mask], dp[mask ^ (1 << bit)]);
            }
        }
    }
}
