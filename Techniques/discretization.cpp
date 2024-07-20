// STL实现离散化
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
// 下标从1开始，olda[i]：数组初始值/不重复的有序值，newa[i]：离散化后的值，olda[newa[i]]：原来的olda[i]
int n, m, olda[N], newa[N];
void init() {
    for (int i = 1; i <= n; i++)
        cin >> olda[i], newa[i] = olda[i];
}

void discre() {
    sort(olda + 1, olda + 1 + n);
    m = unique(olda + 1, olda + 1 + n) - (olda + 1); // 元素个数
    for (int i = 1; i <= n; i++)
        newa[i] = lower_bound(olda + 1, olda + 1 + m, newa[i]) - olda; // 1为最小
}