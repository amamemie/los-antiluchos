#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> poly;

//  NTT (Number Theoretic Transform): FFT con enteros modulo primo
// Requisitos: MOD primo y (MOD-1) multiplo del tamanho (potencia de 2).
// Primos utiles (todos con raiz primitiva 3):
//   998244353  = 119 * 2^23 + 1  -> tamanho maximo 2^23
//   469762049  =   7 * 2^26 + 1  -> tamanho maximo 2^26
//   167772161  =   5 * 2^25 + 1  -> tamanho maximo 2^25
// Si el problema pide otro modulo (ej. 1e9+7): usar multiplicar_mod de fft
const ll MOD = 998244353, RT = 3;

ll addmod(ll a, ll b, ll mod = MOD) { a += b; if (a >= mod) a -= mod; return a; }
ll submod(ll a, ll b, ll mod = MOD) { a -= b; if (a < 0) a += mod; return a; }
ll mulmod(ll a, ll b, ll mod = MOD) { return a * b % mod; }

// b^e mod mod. O(log e)
ll pot(ll b, ll e, ll mod = MOD) {
	ll res = 1;
	b %= mod;
	while (e) {
		if (e & 1) res = res * b % mod;
		b = b * b % mod;
		e >>= 1;
	}
	return res;
}

// Inverso modular (Fermat, mod primo)
ll inv(ll a, ll mod = MOD) { return pot(a, mod - 2, mod); }

// Transformada in-place. a.size() debe ser potencia de 2.
// invertir = false: coeficientes -> valores
// invertir = true : valores -> coeficientes
// O(n log n)
void ntt(poly& a, bool invertir, ll mod = MOD, ll rt = RT) {
	int n = a.size();
	// 1) Permutacion bit-reversal
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	// 2) Mariposas
	for (int len = 2; len <= n; len <<= 1) {
		ll wl = pot(rt, (mod - 1) / len, mod); // raiz primitiva len-esima de la unidad
		if (invertir) wl = inv(wl, mod);
		for (int i = 0; i < n; i += len) {
			ll w = 1;
			for (int j = 0; j < len / 2; j++) {
				ll u = a[i + j];
				ll v = a[i + j + len / 2] * w % mod;
				a[i + j] = addmod(u, v, mod);
				a[i + j + len / 2] = submod(u, v, mod);
				w = w * wl % mod;
			}
		}
	}
	// 3) La inversa divide entre n
	if (invertir) {
		ll ninv = inv(n, mod);
		for (auto& x : a) x = x * ninv % mod;
	}
}

// Producto de polinomios modulo mod. Resultado de tamanho a.size()+b.size()-1.
// Los coeficientes de entrada deben estar en [0, mod). O((n+m) log(n+m))
poly multiply(const poly& a, const poly& b, ll mod = MOD, ll rt = RT) {
	if (a.empty() || b.empty()) return {};
	int need = a.size() + b.size() - 1;
	int n = 1;
	while (n < need) n <<= 1;
	poly fa(a), fb(b);
	fa.resize(n);
	fb.resize(n);
	ntt(fa, false, mod, rt);
	ntt(fb, false, mod, rt);
	for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % mod;
	ntt(fa, true, mod, rt);
	fa.resize(need);
	return fa;
}

// ============================================================
//  Producto EXACTO (sin modulo) con dos NTT + CRT
// ============================================================
// Sirve cuando los coeficientes reales del resultado son < ~4.6e17
// (m1*m2) y los de entrada son >= 0. Por ejemplo, resultados ~1e10 que
// no caben en un solo modulo.
// CRT: x = r1 + m1 * ((r2 - r1) * inv(m1) mod m2)
poly multiplicar_crt(const poly& a, const poly& b) {
	const ll m1 = 998244353, m2 = 469762049;
	poly a1(a), b1(b), a2(a), b2(b);
	for (auto& x : a1) x %= m1;
	for (auto& x : b1) x %= m1;
	for (auto& x : a2) x %= m2;
	for (auto& x : b2) x %= m2;
	poly r1 = multiply(a1, b1, m1, 3);
	poly r2 = multiply(a2, b2, m2, 3);
	ll inv_m1 = inv(m1 % m2, m2);
	poly res(r1.size());
	for (int i = 0; i < (int)res.size(); i++) {
		ll k = submod(r2[i], r1[i] % m2, m2) * inv_m1 % m2;
		res[i] = r1[i] + m1 * k; // < m1*m2 ~ 4.6e17, cabe en ll
	}
	return res;
}
