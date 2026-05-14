// Devuelve sentido horario
vector<point> hull(vector<point> p)
{
    int n = p.size();
	vector<point> h;
	sort(p.begin(),p.end());
	for(int i = 0; i < n; i++){
		while(h.size() >= 2 and p[i].left(h[h.size () - 2], h.back()) < 0){
			h.pop_back();
		}
		h.push_back(p[i]);
	}
	h.pop_back();
	int k = h.size();
	for(int i = n-1; i >= 0; i--)
	{
		while(h.size() >= k + 2 and p[i].left(h[h.size() - 2], h.back()) < 0){
			h.pop_back();
		}
		h.pb(p[i]);
	}
	h.pop_back();
	return h;
}
