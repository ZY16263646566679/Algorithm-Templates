// 快速幂
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
int powTable[11][64];

// 打表
void init_powTable() {
    for (int i = 0; i <= 60; i++)
        powTable[1][i] = 1;
    for (int i = 2; i <= 10; i++) {
        powTable[i][0] = i;
        for (int j = 1; j <= 60; j++)
            powTable[i][j] = powTable[i][j - 1] * powTable[i][j - 1] % mod;
    }
}

int fastPow0(int x, int n) {
    int res = 1;
    for (int i = 0; n >= 1ll << i && i < 64; i++)
        if (n & 1 << i)
            res = (ll)res * powTable[x][i] % mod;
    return res;
}

// 快速幂递归版
int fastPow1(int x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x % mod;
    int t = fastPow1(x, n >> 1) % mod;
    return (ll)t * t % mod * (n & 1 ? x : 1) % mod;
}

// 快速幂非递归版
int fastPow2(int x, int n) {
    int res = 1;
    x %= mod;
    for (; n; n >>= 1) {
        if (n & 1) res = (ll)res * x % mod;
        x = (ll)x * x % mod;
    }
    return res;
}