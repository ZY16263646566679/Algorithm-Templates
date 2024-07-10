// 异或空间线性基
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 64;

ll p[M]; // linear basis
bool zero; // 是否有异或为0的组合

void add(ll x) {
    for (int i = M; i--;)
        if (x >> i == 1) {
            if (!p[i]) {
                p[i] = x;
                return;
            } 
            x ^= p[i];
        }
    zero = true;
}

// 最大异或和：从大到小贪心
ll qmax() {
    ll res = 0;
    for (int i = M; i--;)
        res = max(res, res ^ p[i]);
    return res;
}

// 最小异或和：位数最小的元素
ll qmin() {
    if (zero) return 0;
    for (int i = 0; i < M; i++)
        if (p[i]) return p[i];
    return -1;
}