//  OPERACIONES DE POLINOMIOS (modulo MOD = 998244353)
// REQUIERE: pegar este archivo DEBAJO de ntt (usa poly, MOD,
// addmod, submod, mulmod, pot, inv y multiply).
// Un poly es un vector donde p[i] es el coeficiente de x^i.

// Quita ceros al final (deja al menos 1 coeficiente)
void recortar(poly& p) {
	while (p.size() > 1 && p.back() == 0) p.pop_back();
}

poly sumar(const poly& a, const poly& b) {
	poly r(max(a.size(), b.size()));
	for (int i = 0; i < (int)a.size(); i++) r[i] = addmod(r[i], a[i]);
	for (int i = 0; i < (int)b.size(); i++) r[i] = addmod(r[i], b[i]);
	recortar(r);
	return r;
}

poly restar(const poly& a, const poly& b) {
	poly r(max(a.size(), b.size()));
	for (int i = 0; i < (int)a.size(); i++) r[i] = addmod(r[i], a[i]);
	for (int i = 0; i < (int)b.size(); i++) r[i] = submod(r[i], b[i]);
	recortar(r);
	return r;
}

// Derivada formal. Si p es constante devuelve {0}.
poly derivar(const poly& p) {
	if (p.size() <= 1) return {0};
	poly r(p.size() - 1);
	for (int i = 1; i < (int)p.size(); i++) r[i - 1] = mulmod(p[i], i);
	return r;
}

// Integral formal (constante de integracion = 0). Devuelve tamanho p.size()+1.
poly integrar(const poly& p) {
	int n = p.size();
	poly r(n + 1, 0);
	vector<ll> iv(n + 2, 1); // iv[i] = inverso de i, en O(n)
	for (int i = 2; i <= n; i++) iv[i] = (MOD - (MOD / i) * iv[MOD % i] % MOD) % MOD;
	for (int i = 0; i < n; i++) r[i + 1] = mulmod(p[i], iv[i + 1]);
	return r;
}

// Inverso multiplicativo de b modulo x^n: devuelve c (tamanho n) con b*c = 1 (mod x^n).
// Requiere b[0] != 0. Newton: c <- c * (2 - b*c); cada paso duplica la precision.
poly inversa(const poly& b, int n) {
	poly c = {inv(b[0])};
	for (int len = 1; len < n; len <<= 1) {
		int j = 2 * len;
		poly bb(b);
		bb.resize(j); // solo importan los primeros j coeficientes de b
		poly cb = multiply(c, bb);
		cb.resize(j);
		for (auto& x : cb) x = submod(0, x); // -b*c
		cb[0] = addmod(cb[0], 2);            // 2 - b*c
		c = multiply(c, cb);
		c.resize(j);
	}
	c.resize(n);
	return c;
}

// Division escolar O(n*m): devuelve {cociente, resto}. Rapida si los grados son chicos.
pair<poly, poly> divslow(const poly& a, const poly& b) {
	poly q, r = a;
	ll ib = inv(b.back());
	while (r.size() >= b.size()) {
		ll c = mulmod(r.back(), ib);
		q.push_back(c);
		if (c) {
			for (int i = 0; i < (int)b.size(); i++) {
				int pos = r.size() - 1 - i;
				r[pos] = submod(r[pos], mulmod(c, b[b.size() - 1 - i]));
			}
		}
		r.pop_back();
	}
	reverse(q.begin(), q.end());
	return {q, r};
}

// Division de polinomios: a = q*b + r, con grado(r) < grado(b).
// Devuelve {q, r}. b debe tener coeficiente lider distinto de 0.
// Idea: invirtiendo los coeficientes, q = rev(a) * inversa(rev(b)) mod x^(m-n+1).
pair<poly, poly> dividir(const poly& a, const poly& b) {
	int m = a.size(), n = b.size();
	const int MAGIC = 750; // bajo este umbral la division escolar es mas rapida
	if (m < n) return {{0}, a};
	if (min(m - n, n) < MAGIC) return divslow(a, b);
	poly ap(a), bp(b);
	reverse(ap.begin(), ap.end());
	reverse(bp.begin(), bp.end());
	bp = inversa(bp, m - n + 1);
	poly q = multiply(ap, bp);
	q.resize(m - n + 1);
	reverse(q.begin(), q.end());
	poly r = restar(a, multiply(b, q));
	return {q, r};
}

//  Logaritmo, exponencial y potencia de series de potencias

// ln(a) mod x^n. Requiere a[0] == 1.   ln(a)' = a'/a
poly logaritmo(const poly& a, int n) {
	poly r = multiply(derivar(a), inversa(a, n));
	r.resize(n - 1);
	r = integrar(r); // tamanho n
	return r;
}

// exp(a) mod x^n. Requiere a[0] == 0.
// Newton: g <- g * (1 - ln(g) + a)
poly exponencial(const poly& a, int n) {
	poly g = {1};
	for (int len = 1; len < n; len <<= 1) {
		int j = 2 * len;
		poly lg = logaritmo(g, j);
		poly t(j);
		for (int i = 0; i < j; i++) {
			ll ai = i < (int)a.size() ? a[i] : 0;
			ll li = i < (int)lg.size() ? lg[i] : 0;
			t[i] = submod(ai, li);
		}
		t[0] = addmod(t[0], 1);
		g = multiply(g, t);
		g.resize(j);
	}
	g.resize(n);
	return g;
}

// a^k mod x^n, con k hasta 1e18. Funciona aunque a[0] == 0.
// Se factoriza a = c * x^s * b con b[0] = 1, y a^k = c^k * x^(s*k) * exp(k * ln b).
poly potencia(const poly& a, ll k, int n) {
	poly res(n, 0);
	if (k == 0) { res[0] = 1; return res; }
	int s = 0;
	while (s < (int)a.size() && a[s] == 0) s++;
	if (s == (int)a.size()) return res;          // a = 0
	if (s > 0 && k > (n - 1) / s) return res;    // s*k >= n: todo se sale de x^n
	int desp = s * k;                            // desplazamiento (< n)
	int m = n - desp;                            // coeficientes que realmente se necesitan
	ll c = a[s], ic = inv(c);
	poly b(m, 0);
	for (int i = 0; i < m; i++) if (s + i < (int)a.size()) b[i] = mulmod(a[s + i], ic);
	poly l = logaritmo(b, m);
	ll kk = k % MOD;
	for (auto& x : l) x = mulmod(x, kk);
	poly e = exponencial(l, m);
	ll ck = pot(c, k);
	for (int i = 0; i < m; i++) res[desp + i] = mulmod(e[i], ck);
	return res;
}

//  Evaluacion multipunto e interpolacion
// Arbol de productos: la hoja i es (x - x_i); cada nodo es el producto de
// sus dos hijos. arbol[1] = (x-x_0)(x-x_1)...(x-x_{k-1}).
vector<poly> arbol;

void construir_arbol(const vector<ll>& x) {
	int k = x.size();
	arbol.assign(2 * k, poly());
	for (int i = k; i < 2 * k; i++) arbol[i] = {submod(0, x[i - k] % MOD), 1};
	for (int i = k - 1; i >= 1; i--) arbol[i] = multiply(arbol[2 * i], arbol[2 * i + 1]);
}

// Usa el arbol ya construido. Baja tomando restos: P mod (x - x_i) = P(x_i).
vector<ll> evaluar_arbol(const poly& a, int k) {
	vector<poly> ans(2 * k);
	ans[1] = dividir(a, arbol[1]).second;
	for (int i = 2; i < 2 * k; i++) ans[i] = dividir(ans[i >> 1], arbol[i]).second;
	vector<ll> r(k);
	for (int i = 0; i < k; i++) r[i] = ans[i + k][0];
	return r;
}

// Evalua a en todos los puntos x. O(n log^2 n)
vector<ll> evaluar(const poly& a, const vector<ll>& x) {
	construir_arbol(x);
	return evaluar_arbol(a, x.size());
}

// Interpolacion de Lagrange: dado (x_i, y_i) con x_i distintos, devuelve
// el unico polinomio de grado < k que pasa por todos los puntos.
//   P(x) = sum_i y_i / M'(x_i) * M(x)/(x - x_i),   M = prod (x - x_j)
poly interpolar(const vector<ll>& x, const vector<ll>& y) {
	int k = x.size();
	construir_arbol(x);
	vector<ll> d = evaluar_arbol(derivar(arbol[1]), k); // M'(x_i)
	vector<poly> parcial(2 * k);
	for (int i = k; i < 2 * k; i++) parcial[i] = {mulmod(y[i - k] % MOD, inv(d[i - k]))};
	for (int i = k - 1; i >= 1; i--) {
		poly p1 = multiply(arbol[2 * i], parcial[2 * i + 1]);
		poly p2 = multiply(arbol[2 * i + 1], parcial[2 * i]);
		parcial[i] = sumar(p1, p2);
	}
	return parcial[1];
}
