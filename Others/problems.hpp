#include "head.hpp"

namespace N_Queens {
    int n = 13, grid[16][16]; // 超过13时会超时
    int dfs(int row) {
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (grid[row][i] == 0) {
                if (row == n - 1) {
                    res++;
                    continue;
                }
                for (int j = 1; row + j < n; j++) {
                    grid[row + j][i]++;
                    if (i - j >= 0) grid[row + j][i - j]++;
                    if (i + j < n) grid[row + j][i + j]++;
                }
                res += dfs(row + 1);
                for (int j = 1; row + j < n; j++) {
                    grid[row + j][i]--;
                    if (i - j >= 0) grid[row + j][i - j]--;
                    if (i + j < n) grid[row + j][i + j]--;
                }
            }
        }
        return res;
    }
}

// 约瑟夫环问题，f(n, m)：n个人，m一轮最后剩下的人的下标idx，idx属于[0, n)
// f(1, m)：0
// f(n, m) = (f(n - 1, m) + m) % n

int find(int n, int m) {
    if (n == 1) return 0;
    return (find(n - 1, m) + m) % n;
}

int find(int n, int m) {
    int f[n] {};
    for (int i = 1; i <= n; i++)
        f[i] = (f[i - 1] + m) % i;
    return f[n];
}