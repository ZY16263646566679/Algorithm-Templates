// Rabin-Carp 算法
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

const int base = 131;

bool RabinKarp(string t, string p) {
    int n = t.length(), m = p.length();
    ull h = 1;
    for (int i = 0; i < m - 1; i++)
        h = h * base;
    ull t_hash = 0, p_hash = 0;
    for (int i = 0; i < m; i++) {
        t_hash = base * t_hash + t[i];
        p_hash = base * p_hash + p[i];
    }
    for (int i = 0; i <= n - m; i++) {
        if (t_hash == p_hash) // 找到了
            return true;
        t_hash = base * (t_hash - t[i] * h) + t[i + m]; // 滚动哈希
        i++;
    }
    return false;
}