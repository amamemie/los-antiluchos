// bounded_knapsack para DPs del estilo :
// dp[j - cw] + cv , w-> pesov-> valor y quieres maximizar el valor
int n, we;
cin >> n >> we;
vector<int> v, m, w, dp;
v.resize(n);
m.resize(n);
w.resize(n);
dp.assign(we+1, 0);
int sum = 0;
for(int i  =0 ; i  < n ; i++){
    int a, b, c;
    cin >> a >> b >> c;
    v[i] = a;
    w[i] = b;
    m[i] = c;
    vector<int> old = dp;
    for(int r = 0; r <w[i] and r <= we ;r++){
        deque<pair<int,int>> dq;
        for(int j = r; j <= we ;j +=w[i]){
            int k = (j - r)/w[i];
            while(!dq.empty() and dq.front().first < k - m[i]){
                dq.pop_front();
            }
            int cur = old[j] - k * v[i];
            while(!dq.empty() && dq.back().second <= cur){
                dq.pop_back();
            }
            dq.push_back({k,cur});
            dp[j] = dq.front().second + k * v[i];
        }
    }
}
cout << dp[we];
