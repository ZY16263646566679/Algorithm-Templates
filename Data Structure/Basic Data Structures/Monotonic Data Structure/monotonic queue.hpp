// 单调队列——用于解决滑动窗口最值的问题，时间复杂度O(n)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, m, a[N]; // m：窗口大小
deque<int> q; // 队头->队尾：小->大（用下标存储）

void init() {
    for (int i = 1; i <= m; i++) {
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
    }
}

int slide(int index) {
    while (!q.empty() && a[q.back()] >= a[index]) q.pop_back();
    q.push_back(index);
    while (q.front() <= index - m) q.pop_front();
    return a[q.front()];
}

// 滑动窗口问题也可以用堆和set解决，但是时间复杂度为O(nlogn)

// 静态数组模拟双端队列，效率更高，N：最大可能的push次数
int Q[N], h, t; // size of Q = t - h

void init() {
    for (int i = 1; i <= m; i++) {
        while (h < t && Q[q[t - 1]] >= a[i]) t--;
        Q[t++] = i;
    }
}

int slide(int index) {
    while (h < t && Q[q[t - 1]] >= a[index]) t--;
    Q[t] = index, t++;
    while (Q[q[h]] <= index - m) h++;
    return Q[q[h]];
}

// 若使用循环队列来模拟队列/双端队列，更省空间，用h == t来判断空