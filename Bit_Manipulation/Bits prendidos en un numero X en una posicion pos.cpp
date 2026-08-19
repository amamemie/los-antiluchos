//retorna el numero de bits prendidos
//en una posicion pos desde 0 hasta el numero num
//tambien se puede usar en rangos asi:
//prendidos(R, 1) - prendidos(L-1, 1); 
ll prendidos(ll num, ll pos){
    if(num <= 0){
        return 0;
    }
    ll pote = (1ll << pos);
    ll blocks = (num + 1) / pote;
    ll ones = blocks / 2;
    ones *= pote;
    if(blocks & 1){
        ones += (num + 1) % pote;
    }
    return ones;
}