// 输出期望值模 998244353，bx ≡ a (mod p)，费马小定理求解
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// https://www.luogu.com.cn/problem/P2613
char A[10005], B[10005];
const ll mod = 998244353; // 质数

// 快速幂
ll qpow(ll base, ll exp, ll mod) {
    ll ans = 1;
    while (exp) {
        if (exp & 1)
            ans = (ans * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return ans % mod;
}

int main() {
    fgets(A, 1048576, stdin);
    fgets(B, 1048576, stdin);
    int n = strlen(A), m = strlen(B);
    ll a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        a = (a * 10 + (A[i] - '0')) % mod;
    }
    for (int i = 0; i < m; i++) {
        b = (b * 10 + (B[i] - '0')) % mod;
    }
    if (!b) {
        printf("Angry!");
    } else {
        ll b_inv = qpow(b, mod - 2, mod);
        printf("%lld", (a * b_inv) % mod);
    }
    return 0;
}