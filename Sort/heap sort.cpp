// 堆排序
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;
int a[N];
void heapSort(int l, int r) {
    priority_queue<int, vector<int>, greater<int>> heap;
    for (int i = l; i <= r; i++)
        heap.push(a[i]);
    for (int i = l; i <= r; i++) {
        a[i] = heap.top();
        heap.pop();
    }
}