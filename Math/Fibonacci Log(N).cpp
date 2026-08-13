long long int fibo(int n) {
    long long int a, b, x, y, tmp;
    a = x = tmp = 0;
    b = y = 1;
    while (n != 0)
        if (n % 2 == 0) {
            tmp = a * a + b * b;
            b = b * a + a * b + b * b;
            a = tmp;
            n = n / 2;
        } else {
            tmp = a * x + b * y;
            y = b * x + a * y + b * y;
            x = tmp;
            n = n - 1;
        }
    // x = fibo(n-1)
    return y; // y = fibo(n)
}