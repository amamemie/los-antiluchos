struct HLD {
	int n, act;
	vector<vector<int>> adj;
	vector<int> parent, depth, heavy, head, pos;
	vector<int> val;
	vector<int> seg;
	int tam;
	HLD(int n) : n(n) {
		adj.resize(n+1);
		parent.resize(n+1);
		depth.resize(n+1);
		heavy.assign(n+1, -1);
		head.resize(n+1);
		pos.resize(n+1);
		val.resize(n+1);
		act = 0;
	}
 
	void add_edge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
 
	int dfs(int u, int p) {
		parent[u]=p;
		int size=1, max_sub=0;
		for (int v : adj[u]){
			if(v==p)continue;
			depth[v]=depth[u]+1;
			int sub=dfs(v,u);
			if(sub>max_sub){
				max_sub=sub;
				heavy[u]=v;
			}
			size+=sub;
		}
		return size;
	}
 
	void decompose(int u, int h) {
		head[u]=h;
		pos[u]=act++;
		if(heavy[u]!=-1)decompose(heavy[u], h);
		for(int v: adj[u]){
			if(v!=parent[u] and v!=heavy[u])decompose(v,v);
		}
	}
 
	void build(){
		tam=1;
		while (tam < n) tam<<=1;
		seg.assign(2*tam,inf);
		for (int i = 1; i <= n; i++){
			seg[tam+pos[i]]=val[i];
		}
		for (int i = tam - 1; i > 0; i--){
			seg[i]=max(seg[2*i],seg[2*i+1]);
		}
	}
 
	void update(int u, int value) {
		int i=tam+pos[u];
		seg[i]=value;
		for(i>>=1; i; i>>=1){
			seg[i]=max(seg[2*i],seg[2*i+1]);
		}
	}
 
	int query(int l, int r) { 
		int res=inf;
		l+=tam;
		r+=tam;
		while(l <= r){
			if(l&1)res=max(res,seg[l++]);
			if(!(r&1))res=max(res,seg[r--]);
			l>>=1;
			r>>=1;
		}
		return res;
	}
 
	void init(){
		int root=1;
		dfs(root, 0);
		decompose(root,root);
		build();
	}
 
	int query_path(int a, int b){
		int res=inf;
		while(head[a]!=head[b]){
			if(depth[head[a]]<depth[head[b]])swap(a,b);
			res=max(res,query(pos[head[a]],pos[a]));
			a=parent[head[a]];
		}
		if(depth[a]>depth[b])swap(a,b);
		res=max(res,query(pos[a],pos[b]));
		return res;
	}
};

void solve(){
	int n,q;
	cin>>n>>q;
	HLD hld(n);
	for(int i = 1 ; i <= n ; i++){
		cin>>hld.val[i];
	}
	for(int i = 0; i  < n-1 ; i++){
		int a,b;
		cin>>a>>b;
		hld.add_edge(a,b);
	}
	hld.init();
	while(q--){
		int t;
		cin>>t;
		if(t==1){
			int s,x;
			cin>>s>>x;
			hld.update(s,x);
		}
		else{
			int a,b;
			cin>>a>>b;
			cout<<hld.query_path(a,b)<<' ';
		}
	}
}
