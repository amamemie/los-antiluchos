//Counting Numbers CSES
//PyroxBoy 
ll dp[20][11][2][2];
//pos, last, tight, started for leading zeroes
 
ll a, b;
 
int tam;
string aux;
 
ll f(int pos, int last, int tight, int start){
    if(pos > tam){
        return 1;
    }
    ll &ans = dp[pos][last][tight][start];
    if(ans == -1){
        ans = 0;
        int lim = 9;
 
        if(tight){
            lim = aux[pos] - '0';
        }
        int ultimo = aux[pos] - '0';
        for(int d = 0; d <= lim; d++){
            if(d == last and start){
                continue;
            }
            int ntight = 0;
            if(tight and d == ultimo){
                ntight = 1;
            }
            int nstart = start;
            if(!start and d != 0){
                nstart = 1;
            }   
            ans += f(pos+1, d, ntight, nstart);
        }
    }
    return ans;
}
 
ll reco(ll x){
    if(x < 0){
        return 0;
    }
    aux = to_string(x);
    memset(dp, -1, sizeof(dp));
    tam = aux.size()-1;
    return f(0, 10, 1, 0);
}
void solve(){
    cin >> a >> b;
    f(0, 10, 1, 0);
    ll ans = reco(b) - reco(a-1);
    cout << ans << "\n";
}
 
//Sabroseando el code.
//Leer es clave.
//Upsolvear duele.
//Perseverancia, Paciencia, Providencia.
//Diamonds are made under pressure
