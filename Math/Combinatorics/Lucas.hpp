// Lucas 定理求组合数，适用于模数比较小的情况
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int p; // p 是素数

// 费马小定理求逆元
int inv(int x) {
    int res = 1;
    for (int n = p - 2; n; n >>= 1) {
        if (n & 1) res = (ll)res * x % p;
        x = (ll)x * x % p;
    }
    return res;
}

// 逆元求组合数
int comb(int n, int m) {
    if (m > n) return 0;
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = (ll)res * i % p;
    for (int i = 1; i <= m; i++)
        res = (ll)res * inv(i) % p;
    for (int i = 1; i <= n - m; i++)
        res = (ll)res * inv(i) % p;
    return res;
}

// Lucas 定理求组合数
int lucas(int n, int m) {
    int res = 1;
    for (; n || m; n /= p, m /= p) {
        int a = n % p, b = m % p;
        res = (ll)res * comb(a, b) % p;
    }
    return res;
}
