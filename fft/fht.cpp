#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

//  FHT: Fast Hadamard / Walsh-Hadamard Transform
// Convoluciones sobre MASCARAS DE BITS (en vez de suma de indices):
//   XOR: c[k] = sum de a[i]*b[j] con i ^ j = k
//   AND: c[k] = sum de a[i]*b[j] con i & j = k
//   OR : c[k] = sum de a[i]*b[j] con i | j = k
// El tamanho n debe ser potencia de 2 (n = 2^bits). Complejidad O(n log n).
// Todo se hace modulo MOD. Si necesitas valores exactos (sin modulo),
// quita los "% MOD" y en la inversa XOR divide directo entre n.
const ll MOD = 1000000007;

ll pot(ll b, ll e) {
	ll res = 1;
	b %= MOD;
	while (e) {
		if (e & 1) res = res * b % MOD;
		b = b * b % MOD;
		e >>= 1;
	}
	return res;
}

// ---------- XOR ----------
// La mariposa (u, v) -> (u+v, u-v) es la transformada de Walsh-Hadamard.
// La inversa es la misma operacion y luego dividir entre n.
void fht_xor(vl& a, bool invertir) {
	int n = a.size();
	for (int len = 1; len < n; len <<= 1) {
		for (int i = 0; i < n; i += 2 * len) {
			for (int j = 0; j < len; j++) {
				ll u = a[i + j], v = a[i + j + len];
				a[i + j] = (u + v) % MOD;
				a[i + j + len] = (u - v + MOD) % MOD;
			}
		}
	}
	if (invertir) {
		ll ninv = pot(n, MOD - 2);
		for (auto& x : a) x = x * ninv % MOD;
	}
}

// ---------- AND ----------
// Transformada zeta sobre SUPERCONJUNTOS: f^[S] = suma de f[T] con T contiene a S.
// Luego AND-convolucion = producto punto a punto.
// La inversa resta en vez de sumar (Mobius).
void fht_and(vl& a, bool invertir) {
	int n = a.size();
	for (int len = 1; len < n; len <<= 1) {
		for (int i = 0; i < n; i += 2 * len) {
			for (int j = 0; j < len; j++) {
				ll& u = a[i + j];
				ll v = a[i + j + len];
				if (!invertir) u = (u + v) % MOD;
				else u = (u - v + MOD) % MOD;
			}
		}
	}
}

// ---------- OR ----------
// Transformada zeta sobre SUBCONJUNTOS: f^[S] = suma de f[T] con T dentro de S.
// Luego OR-convolucion = producto punto a punto.
void fht_or(vl& a, bool invertir) {
	int n = a.size();
	for (int len = 1; len < n; len <<= 1) {
		for (int i = 0; i < n; i += 2 * len) {
			for (int j = 0; j < len; j++) {
				ll u = a[i + j];
				ll& v = a[i + j + len];
				if (!invertir) v = (v + u) % MOD;
				else v = (v - u + MOD) % MOD;
			}
		}
	}
}

// ---------- Convoluciones completas ----------
// a y b deben tener el mismo tamanho (potencia de 2).
vl conv_xor(vl a, vl b) {
	fht_xor(a, false);
	fht_xor(b, false);
	for (int i = 0; i < (int)a.size(); i++) a[i] = a[i] * b[i] % MOD;
	fht_xor(a, true);
	return a;
}

vl conv_and(vl a, vl b) {
	fht_and(a, false);
	fht_and(b, false);
	for (int i = 0; i < (int)a.size(); i++) a[i] = a[i] * b[i] % MOD;
	fht_and(a, true);
	return a;
}

vl conv_or(vl a, vl b) {
	fht_or(a, false);
	fht_or(b, false);
	for (int i = 0; i < (int)a.size(); i++) a[i] = a[i] * b[i] % MOD;
	fht_or(a, true);
	return a;
}

// Potencia de una familia bajo XOR-convolucion (a^k): transformar una vez,
// elevar cada posicion a k y volver. O(n log n + n log k)
vl potencia_xor(vl a, ll k) {
	fht_xor(a, false);
	for (auto& x : a) x = pot(x, k);
	fht_xor(a, true);
	return a;
}

// ============================================================
//  Ejemplo: Sum the Fibonacci (914G)
// ============================================================
// Con 17 bits, n = 1 << 17. Se arman tres arreglos indexados por mascara
// (pares (a,b) con a&b=0 agrupados por a|b; elementos simples; pares (d,e)
// agrupados por xor) y se combinan con conv_and. Luego solo importan las
// mascaras con un unico bit, a las que se les multiplica el Fibonacci.
