#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int cnt, prime[N]; // cnt：素数个数
bool vis[N]; // 是否被筛

// 埃式筛（时间复杂度约等于O(n)）
int E_sieve(int n) {
    for (int i = 2; i * i <= n; i++)
        if (!vis[i])
            for (int j = i * i; j <= n; j += i)
                vis[j] = true;
    int cnt = 0;
    for (int i = 2; i <= n; i++)
        if (!vis[i]) cnt++;
    return cnt;
}

// 欧拉筛（线性筛，O(n)）
void euler_sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && i * prime[j] <= n; j++) { // 筛掉i的素数倍
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break; // 保证每个合数只被它最小的质因数筛一次，从而保证线性
        }
    }
}

/**
 * 关于为什么每个合数只会被它最小的质因数筛一次：
 * 因为i % prime[j] == 0后，再往后筛的话，被筛掉的数的最小质因数就不是后面的prime[j]了，而是第一次i % prime[j] == 0时的prime[j]（这个prime[j]更小）
 */

// 换用bitset后比欧拉筛时间效率还要高一点点
bitset<N> vis;
int E_sieve(int n) {
    for (int i = 2; i * i <= n; i++)
        if (!vis[i])
            for (int j = i * i; j <= n; j += i)
                vis[j] = 1;
    int cnt = 0;
    for (int i = 2; i <= n; i++)
        if (!vis[i]) cnt++;
    return cnt;
}

// 另一种写法
void getPrime(int n) {
    for (int i = 2; i <= n; i++) {
        if (vis[i]) continue;
        prime[cnt++] = i;
        for (int j = i * i; j <= n; j += i)
            vis[j] = true;
    }
}