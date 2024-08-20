// 欧拉函数
#include <bits/stdc++.h>
using namespace std;

/**
 * 欧拉定理：
 * 若 (m, n) = 1，m ^ φ(n) ≡ 1 (mod n)
 * φ(n)：小于等于n的所有数中与n互质的数的个数
 */

// 求解单个欧拉函数，时间复杂度O(√n)
int euler(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    if (n > 1) res -= res / n;
    return res;
}

// 线性筛求1~n内所有的欧拉函数，时间复杂度O(n)
const int N = 1e5 + 5;
int n, phi[N];
bool vis[N];
vector<int> primes;

void get_phi() {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = true;
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) break;
            vis[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}