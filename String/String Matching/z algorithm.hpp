// Z 函数
#include <bits/stdc++.h>
using namespace std;

/**
 * z[i]：下标 i 开始的后缀与 s 的最长公共前缀（lcp）的长度
 */
const int N = 1e6 + 5;
int z[N];

void getZ(string s) {
    int n = s.length(); // 定义 Z box
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r && z[i - l] < r - i + 1)
            z[i] = z[i - l];
        else {
            z[i] = max(0, r - i + 1);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        }
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
}