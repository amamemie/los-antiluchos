//Algoritmo para menor rotacion lexicografíca de un string en O(N)

int menorRotacion(string &s){
    int n = s.size();
    vector<int>f(2*n, -1);
    int k = 0; //indice mejor rotacion
    for(int j = 1; j < 2*n;j++){
        int i = f[j-k-1];
        //el operador %n simula la concatenacion de la cadena s+s
        while(i!=-1 and s[j%n]!=s[(k+i+1)%n]){
            if(s[j%n] < s[(k+i+1)%n]){
                k = j - i - 1;
            }
            i = f[i];
        }
        if(i == -1 and s[j%n] != s[(k+i+1)%n]){
            if(s[j % n] < s[(k+i+1%n)]){
                k = j;
            }
            f[j - k] = -1;
        }
        else{
            f[j - k] = i + 1;
        }
    }
    return k;
}
void solve(){
    string s;
    cin >> s;
    ll n = s.size();
    ll ans = menorRotacion(s);
    repl(i, ans, ans+n){
        cout << s[i%n];
    }
}  
