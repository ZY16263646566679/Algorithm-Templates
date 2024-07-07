// 逆元
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int p = 998244353;

/**
 * 费马小定理求逆元
 * Fermat's little theorem（费马小定理）
 * 若 p 为质数，a 为整数，则 a^p-1 ≡ 1(mod p)
 * 因此，a 的逆元为 a^(p-2)，可以用快速幂求解
 */
int fermat(int x) {
    int res = 1;
    for (int n = p - 2; n; n >>= 1) {
        if (n & 1) res = (ll)res * x % p;
        x = (ll)x * x % p;
    }
    return res;
}

// 线性递推求逆元
const int N = 1e7 + 5;
int inv[N];

void init() {
    inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = ll(p - p / i) * inv[p % i] % p;
}

// 扩展欧几里得算法求逆元
// 详见 extend gcd.hpp