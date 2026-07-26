const int N = 1e5 + 10;
int odd[N]; //odd[i] = max odd palindrome centered on i
int even[N]; //even[i] = max even palindrome centered on i
void manacher(string & s) {
    int l = 0, r = -1, n = s.size();
    for (int i = 0; i < n; i++) {
        int k = i > r ? 1 : min(odd[l + r - i], r - i);
        while (i + k < n and i - k >= 0 and s[i + k] == s[i - k]) k++;
        odd[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    l = 0;
    r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 0 : min(even[l + r - i + 1], r - i + 1);
        k++;
        while (i + k <= n and i - k >= 0 and s[i + k - 1] == s[i - k]) k++;
        even[i] = --k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
}
