array<ll, 3> get_canonical(ll px, ll py, ll qx, ll qy){
    ll a = 2 * (qx - px);
    ll b = 2 * (qy - py);
    ll c = px*px + py*py - qx*qx - qy*qy;
    ll g = gcd(a, gcd(b, c));
    a /= g; b /= g; c /= g;
    if(a < 0) a = -a, b = -b, c = -c;
    if(a == 0 and b < 0) b = -b, c = -c;
    return {a,b,c}; 
}
void solve(){
    ll px,py,qx,qy,rx,ry,sx,sy;
    cin >> px >> py >> qx >> qy >> rx >> ry >> sx >> sy;
    array<ll, 3> uwu = get_canonical(px,py,qx,qy);
    array<ll, 3> owo = get_canonical(rx,ry,sx,sy);
    if(uwu[0]*owo[1] == owo[0]*uwu[1]){ // is perpendicular
        if(uwu == owo){ // same line
            cout << "Yes\n";
        }
        else{
            cout << "No\n";
        }
    }
    else{
        cout << "Yes\n";
    }
}
