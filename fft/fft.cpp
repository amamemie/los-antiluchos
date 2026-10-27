#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;

//  FFT con numeros complejos (double)
// Cuando usarla: resultados enteros "grandes" que NO se quieren
// reducir modulo nada (ej: contar pares, hasta ~1e14 de resultado).
// Precision: es exacta si los coeficientes del resultado son menores
// a ~1e14 (regla practica: n * maxA * maxB < 1e14 aprox).
// Si el resultado es mayor, usar NTT con 2 modulos + CRT (ver 2_ntt.cpp)
// o multiplicar_mod mas abajo si te piden un modulo cualquiera.
const double PI = acos(-1.0);

// Transformada in-place. a.size() debe ser potencia de 2.
// invertir = false: coeficientes -> valores
// invertir = true : valores -> coeficientes (divide entre n al final)
// Complejidad: O(n log n)
void fft(vector<cd>& a, bool invertir) {
	int n = a.size();
	// 1) Permutacion bit-reversal
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	// 2) Tabla de raices n-esimas de la unidad calculadas directamente
	//    con cos/sin (mas precisas que ir multiplicando w *= wl).
	vector<cd> w(n / 2);
	for (int i = 0; i < n / 2; i++) {
		double ang = 2 * PI * i / n;
		w[i] = cd(cos(ang), invertir ? -sin(ang) : sin(ang));
	}
	// 3) Mariposas
	for (int len = 2; len <= n; len <<= 1) {
		int paso = n / len; // la raiz len-esima es w[j * paso]
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < len / 2; j++) {
				cd u = a[i + j];
				cd v = a[i + j + len / 2] * w[j * paso];
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
			}
		}
	}
	// 4) La inversa divide entre n
	if (invertir) for (auto& x : a) x /= n;
}

// Producto de polinomios con coeficientes enteros (pueden ser negativos).
// Resultado de tamanho a.size() + b.size() - 1. O((n+m) log(n+m))
vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
	if (a.empty() || b.empty()) return {};
	int need = a.size() + b.size() - 1;
	int n = 1;
	while (n < need) n <<= 1;
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, true);
	vector<ll> res(need);
	for (int i = 0; i < need; i++) res[i] = llround(fa[i].real()); // redondear
	return res;
}

// Producto modulo un modulo CUALQUIERA (ej: 1e9+7). Requiere 0 <= a[i] < mod <= 2^30.
// Idea: partir cada coeficiente en dos mitades de 15 bits para que los
// productos intermedios sean chicos y los doubles no pierdan precision.
//   a = a1*2^15 + a0,  b = b1*2^15 + b0
//   a*b = a1*b1*2^30 + (a0*b1 + a1*b0)*2^15 + a0*b0
vector<ll> multiplicar_mod(const vector<ll>& a, const vector<ll>& b, ll mod) {
	if (a.empty() || b.empty()) return {};
	int need = a.size() + b.size() - 1;
	int n = 1;
	while (n < need) n <<= 1;
	vector<cd> a0(n), a1(n), b0(n), b1(n);
	for (int i = 0; i < (int)a.size(); i++) a0[i] = a[i] & 32767, a1[i] = a[i] >> 15;
	for (int i = 0; i < (int)b.size(); i++) b0[i] = b[i] & 32767, b1[i] = b[i] >> 15;
	fft(a0, false); fft(a1, false);
	fft(b0, false); fft(b1, false);
	vector<cd> r00(n), r01(n), r11(n);
	for (int i = 0; i < n; i++) {
		r00[i] = a0[i] * b0[i];
		r01[i] = a0[i] * b1[i] + a1[i] * b0[i];
		r11[i] = a1[i] * b1[i];
	}
	fft(r00, true); fft(r01, true); fft(r11, true);
	vector<ll> res(need);
	for (int i = 0; i < need; i++) {
		ll x00 = llround(r00[i].real()) % mod;
		ll x01 = llround(r01[i].real()) % mod;
		ll x11 = llround(r11[i].real()) % mod;
		res[i] = (x00 + (x01 << 15) % mod + (x11 << 30) % mod) % mod;
	}
	return res;
}
