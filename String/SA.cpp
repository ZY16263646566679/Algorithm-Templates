// 后缀数组，可用于求解最长重复子串、最长公共子串
#include <bits/stdc++.h>
using namespace std;
    
const int N = 3e5 + 5;
char s[N]; // 下标从1开始，scanf("%s", s + 1)
int n, sa[N], rk[N << 1], tmp[N << 1]; // sa[i]: 排名为 i 的后缀的起始位置，rk[i]: s[i..n] 的排名（范围1~n）

// 倍增法求 SA
void init_sa() { // index: [1, n]
    for (int i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
        for (int k = 1; k < n; k <<= 1) {
            sort(sa + 1, sa + n + 1, [&](int x, int y) {
                return rk[x] == rk[y] ? rk[x + k] < rk[y + k] : rk[x] < rk[y];
            });  // 这里用到了 lambda
            memcpy(tmp, rk, sizeof(rk));
            // 由于计算 rk 的时候原来的 rk 会被覆盖，要先复制一份
            for (int p = 0, i = 1; i <= n; i++)
                if (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + k] == tmp[sa[i - 1] + k])
                    rk[sa[i]] = p;
                else rk[sa[i]] = ++p; // 若两个子串相同，它们对应的 rk 也需要相同，所以要去重
      }
}

int h[N]; // h[i]: sa[i - 1] 和 sa[i] 的最长公共前缀长度

void get_h() {
    for (int i = 1, k = 0; i <= n; i++) {
        if (rk[i] == 0) continue;
        if (k) k--;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) k++;
        h[rk[i]] = k;
    }
}