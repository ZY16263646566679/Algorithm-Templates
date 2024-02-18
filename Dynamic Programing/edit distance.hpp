// 编辑距离
#include <bits/stdc++.h>
using namespace std;

#define min(a, b, c) (a <= b ? a <= c ? a : c : b <= c ? b : c)
const int N = 2005;
string s1, s2; // s1 -> s2
int m, n, dp[N][N]; // m：s1的长的，n：s2的长度

int edit() {
    for (int i = 1; i <= m; i++) dp[i][0] = i;
    for (int i = 1; i <= n; i++) dp[0][i] = i;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
    return dp[m][n];
}