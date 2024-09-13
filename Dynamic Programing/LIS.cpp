// 最长递增子序列（longest increasing subsequence）
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int n, a[N]; // 下标从0开始
vector<int> ed; // end[i]：长度为i + 1的递增子序列的最小末尾值

// 贪心+二分，时间复杂度O(nlogn)
int lis() {
    for (int i = 0; i < n; i++) {
        auto p = lower_bound(ed.begin(), ed.end(), a[i]); // 如果是求最长不递增子序列，换成upper_bound即可
        if (p == ed.end()) ed.push_back(a[i]);
        else *p = a[i];
    }
    return ed.size();
}