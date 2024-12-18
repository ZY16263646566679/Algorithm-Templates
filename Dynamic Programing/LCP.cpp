// 最长公共前缀（LCP）
#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;
int n, m;
string s1, s2;
int lcp[N][N];

void getLCP() {
    for (int i = n; i--;)
        for (int j = m; j--;) {
            if (s1[i] != s2[j]) continue;
            lcp[i][j] = lcp[i + 1][j + 1] + 1;
        }
}

