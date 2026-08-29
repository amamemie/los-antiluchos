ll base[LOG];
ll tam = 0;
void add(ll msk){
	for(int i = LOG-1; i>= 0; i--){
		if(!(msk&(1LL<<i)))continue;
		if(!base[i]){
			base[i]=msk;
			tam++;
			return;
		}
		msk^=base[i];
	}
}
