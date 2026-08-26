void solve(){
    //mapa de caracteres en windows para ~
    int a, x;
    cin >> a >> x; // a es el numero, x es el numero de bit
    //los bits se enumeran de dercha a izquierda iniciando de 0
    /*
    Ej: n = 8
    Binario:     1 0 0 0
    Posicion:    3 2 1 0
    */
    a = a & ~(1 << x); //apagamos el bit x de a
    cout << a << "\n";
} 
