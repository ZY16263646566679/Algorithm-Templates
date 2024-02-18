// 快速幂
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
ll powTable[11][64];
void init_powTable() {
    for (int i = 0; i <= 60; i++)
        powTable[1][i] = 1;
    for (int i = 2; i <= 10; i++) {
        powTable[i][0] = i;
        for (int j = 1; j <= 60; j++)
            powTable[i][j] = powTable[i][j - 1] * powTable[i][j - 1] % mod;
    }
}

ll fastPow0(int x, ll n) {
    ll res = 1;
    for (int i = 0; n >= 1ull << i && i < 64; i++)
        if (n & 1 << i)
            res = res * powTable[x][i] % mod;
    return res;
}

ll fastPow(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x % mod;
    ll temp = fastPow(x, n >> 1) % mod;
    if (n & 1) return temp * temp * x % mod;
    return temp * temp % mod;
}

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