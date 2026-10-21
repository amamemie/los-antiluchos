#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MOD = 1e9 + 7;

struct Matrix {
    ll a[2][2];
    Matrix() {
        memset(a, 0, sizeof(a));
    }
};

Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
            }
        }
    }
    return C;
}

Matrix power(Matrix A, ll n) {
    Matrix R;
    R.a[0][0] = 1;
    R.a[1][1] = 1;
    while (n) {
        if (n & 1)
            R = multiply(R, A);
        A = multiply(A, A);
        n >>= 1;
    }
    return R;
}

ll fibonacci(ll n) {
    if (n == 0) return 0;
    Matrix A;
    A.a[0][0] = 1;
    A.a[0][1] = 1;
    A.a[1][0] = 1;
    A.a[1][1] = 0;
    Matrix R = power(A, n - 1);
    return R.a[0][0];
}

int main() {
    ll n;
    cin >> n;
    cout << fibonacci(n) << '\n';
}