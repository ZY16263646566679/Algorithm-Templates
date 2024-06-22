// 线性递推求逆元
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e7 + 5;
int p, inv[N];

void init() {
    inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = (ll)(p - p / i) * inv[p % i] % p;
}