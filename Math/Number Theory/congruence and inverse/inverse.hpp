// 逆元
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int p = 998244353;

/**
 * 费马小定理求逆元：
 * 1）逆元：
 * 若 (a, p) = 1 且 a * x ≡ 1(mod p)，则称 x 为 a 的逆元
 * 2）费马小定理（Fermat's little theorem）：
 * 若 p 为质数，p ∤ a，则 a^(p-1) ≡ 1(mod p)
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

// 扩展欧几里得算法求逆元
// 详见 extend Euclidean.hpp

// 线性递推求多个逆元
const int N = 1e7 + 5;
int inv[N];

void init() {
    inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = ll(p - p / i) * inv[p % i] % p;
}