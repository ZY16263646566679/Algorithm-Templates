// 判断素数
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 试除法
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// Miller-Rabin素性测试
int a[7] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }; // ll范围内100%正确，int：2, 7, 61

ll fastPow(ll x, ll n, int mod) { // 快速幂非递归版
    ll res = 1;
    x %= mod;
    while (n) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

bool check(ll a, ll n) { // 检验是否为合数
    ll u = n - 1;
    int t = 0;
    while ((u & 1) == 0) u >>= 1, t++;
    ll x1, x2;
    x1 = fastPow(a, u, n);
    for (int i = 1; i <= t; i++) {
        x2 = fastPow(x1, 2, n);
        if (x2 == 1 && x1 != 1 && x1 != n - 1) return true;
        x1 = x2;
    }
    if (x1 != 1) return true;
    return false;
}

bool miller_rabin(ll n) { // Miller-Rabin素性检验
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 0; i < 7; i++)
        if (check(a[i], n)) return false;
    return true;
}