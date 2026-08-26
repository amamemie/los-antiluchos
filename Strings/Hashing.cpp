struct Hash {
	long long P=1777771,MOD[2],PI[2];
	vector<long long> h[2],pi[2];

	// SOLO PARA ROLLING / JOIN:
	vector<long long> pw[2];

	Hash(string& s){
		MOD[0]=999727999;
		MOD[1]=1070777777;
		PI[0]=325255434;
		PI[1]=10018302;

		for(int k = 0; k < 2; k++) {
			h[k].resize(s.size()+1);
			pi[k].resize(s.size()+1);

			// SOLO PARA ROLLING / JOIN:
			pw[k].resize(s.size()+1);
		}

		for(int k = 0; k < 2; k++){
			h[k][0] = 0;
			pi[k][0] = 1;

			// SOLO PARA ROLLING / JOIN:
			pw[k][0] = 1;

			long long p = 1;

            for(int i = 1; i < s.size()+1; i++){
				h[k][i] = (h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i] = (1LL*pi[k][i-1]*PI[k])%MOD[k];

				// SOLO PARA ROLLING / JOIN:
				pw[k][i] = (1LL*pw[k][i-1]*P)%MOD[k];

				p = (p*P)%MOD[k];
			}
		}
	}

	long long get(int s, int e){
		long long h0 = (h[0][e]-h[0][s]+MOD[0])%MOD[0];
		h0 = (1LL*h0*pi[0][s])%MOD[0];

		long long h1 = (h[1][e]-h[1][s]+MOD[1])%MOD[1];
		h1 = (1LL*h1*pi[1][s])%MOD[1];

		return (h0<<32)|h1;
	}

	// SOLO PARA ROLLING / JOIN:
	long long join(long long a, long long b, int lenA){
		long long a0 = a>>32;
		long long a1 = a&0xffffffffLL;

		long long b0 = b>>32;
		long long b1 = b&0xffffffffLL;

		a0 = (a0 + b0*pw[0][lenA])%MOD[0];
		a1 = (a1 + b1*pw[1][lenA])%MOD[1];

		return (a0<<32)|a1;
	}
};