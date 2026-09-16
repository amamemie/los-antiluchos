vector<ll> get_lis(vector<ll> &v){
    vector<ll> ans;
    ans.push_back(v[0]);
    for(ll x : v){
        if(x > ans.back()){
            ans.push_back(x);
        }
        else{
            ll low = lower_bound(ans.begin(), ans.end(), x) - ans.begin();
            ans[low] = x;
        }
    }
    return ans;
}