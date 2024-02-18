// 归并排序
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int a[N];
void mergeSort(int l, int r) { // 将[l, r)内元素升序排序
    if (r - l <= 1) return;
    int mid = (l + r) >> 1;
    if (mid - l >= 2) mergeSort(l, mid);
    if (r - mid >= 2) mergeSort(mid, r);
    int* t = new int[mid - l], now = l, p1 = 0, p2 = mid;
    for (int i = 0; i < mid  - l; i++)
        t[i] = a[l + i];
    while (p1 < mid - l && p2 < r)
        if (t[p1] <= a[p2]) a[now++] = t[p1++];
        else a[now++] = a[p2++];
    while (p1 < mid - l) a[now++] = t[p1++];
}

// 求区间[l, r)内逆序对的个数（i < j，a[i] > a[j]）
int inversion(int l, int r) {
    if (r - l <= 1) return 0;
    int res = 0, mid = (l + r) >> 1;
    if (mid - l >= 2) res += inversion(l, mid);
    if (r - mid >= 2) res += inversion(mid, r);
    int* t = new int[mid - l], now = l, p1 = 0, p2 = mid;
    for (int i = 0; i < mid  - l; i++)
        t[i] = a[l + i];
    while (p1 < mid - l && p2 < r)
        // 当两者相等的时候必须要移动p1，不可移动p2，否则可能会漏数
        if (t[p1] <= a[p2]) a[now++] = t[p1++];
        else {
            res += mid - l - p1;
            a[now++] = a[p2++];
        }
    while (p1 < mid - l) a[now++] = t[p1++];
    return res;
}

template<typename T>
void mergeSort(T* begin, T* end) {
    if (end - begin <= 1) return;
    int n = end - begin, mid = n >> 1;
    mergeSort(begin, begin + mid);
    mergeSort(begin + mid, end);
    // inplace_merge(begin, begin + mid, end); // 原地归并，时间复杂度较高O(nlogn)
    T* temp = new T[mid];    // 使用额外数组，时间复杂度较低O(n)
    for (int i = 0; i < mid; i++) // 只复制前半部分，在原数组上合并
        temp[i] = begin[i];
    int i = 0, j = mid, pos = 0; // i指向temp，j指向begin，pos指向已经合并完的末尾
    while (i < mid && j < n)
        begin[pos++] = temp[i] <= begin[j] ? temp[i++] : begin[j++];
    while (i < mid) begin[pos++] = temp[i++];
}