struct point{
    long long x,y;
};
long long sq(long long a){
    return a * a;
}
long long distance(point a, point b){
    long long A = sq((a.x - b.x));
    long long B = sq((a.y - b.y));
    return A + B;
}
long long closest(vector<point>& X, vector<point>& Y){
    int n = X.size();
    if(n <= 1){
        return LLONG_MAX;
    }
    vector<point> left_x = vector<point>(X.begin(), X.begin() + (n / 2));
    vector<point> right_x = vector<point>(X.begin() + (n / 2), X.end());
    vector<point> left_y, right_y;
    for(point p : Y){
        if(make_pair(p.x, p.y) <= make_pair(left_x.back().x, left_x.back().y)){
            left_y.push_back(p);
        }
        else{
            right_y.push_back(p);
        }
    }
    long long d1 = closest(left_x, left_y);
    long long d2 = closest(right_x, right_y);
    long long d = min(d1,d2);
    long long mid_x = left_x.back().x;
    vector<point> stripe;
    for(point& p : Y){
        if(sq(p.x - mid_x) < d){ 
            stripe.push_back(p);
        }
    }
    for(int i = 0; i < (int) stripe.size(); i++){
        for(int j = i + 1; j < (int) stripe.size() and sq(stripe[j].y - stripe[i].y) < d; j++){
            d = min(d, distance(stripe[i], stripe[j]));
        }
    }
    return d;
}
void solve(){
    int n; cin >> n;
    vector<point> v(n);
    for(point& x : v){
        cin >> x.x >> x.y;
    }
    sort(v.begin(),v.end(), [&](const point& a, const point& b){
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    vector<point> w = v;
    sort(w.begin(),w.end(),[&](const point& a, const point& b){
        return a.y < b.y;
    });
    long long ans = closest(v,w);
    cout << ans << "\n";
}
