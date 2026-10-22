// Uso: saber que sumas se pueden formar eligiendo un subconjunto.
// Costo: O(n * M / 64), M = suma maxima. Memoria: M/8 bytes.
const int M = 1000001;          // tamaño FIJO en compilacion (suma max + 1)
static bitset<M> S;
S[0] = 1;
for (int v : vals) S |= S << v; // no tomo v | si tomo v

// Operaciones utiles
S.count();                      // cuantas sumas distintas
S[k];                           // se puede formar k?
S._Find_first(); S._Find_next(i); // recorrer sumas alcanzables
(S << x)                        // sumar x a TODOS los elementos
A | B                           // union de conjuntos
