// 快速排序
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;
int a[N];
void quickSort(int l, int r) { // 将[l, r)内元素升序排序
    if (r - l <= 1) return;
    int s = l;
    // make sure a[i] < a[r - 1], i in [l, s) and a[i] >= a[r - 1], i in [s, r)
    for (int f = s; f < r - 1; f++)
        if (a[f] < a[r - 1]) {
            if (s < f) swap(a[s], a[f]);
            s++;
        }
    swap(a[s], a[r - 1]);
    quickSort(l, s);
    quickSort(s + 1, r);
}

// 求区间[0, r)内第k大数
int kth_num(int l, int r, int k) { // 调用：kth_num(0, r, k)
    if (r - l <= 1) return a[k - 1];
    if (r - l == 2) {
        if (a[l] > a[l + 1]) swap(a[l], a[l + 1]);
        return a[k - 1];
    }
    int s = l, f = l;
    while (f < r - 1) {
        if (a[f] < a[r - 1]) {
            if (s < f) swap(a[s], a[f]);
            s++;
        }
        f++;
    }
    swap(a[s], a[r - 1]);
    if (s < k - 1) return kth_num(s + 1, r, k);
    if (s > k - 1) return kth_num(l, s, k);
    return a[k - 1];
}

// 数组元素数小于3,000,000时快速排序比归并排序快
void quickSort(int* begin, int* end) {
    if (end - begin <= 1) return;
    if (end - begin == 2) {
        if (*begin > *(end - 1))
            swap(*begin, *(end - 1));
        return;
    }
    int* part = begin - 1, * it = begin - 1, base = *(end - 1);
    while (++it < end)
        if (*it < base)
            if (++part < it)
                swap(*part, *it);
    swap(*++part, *(end - 1)); // 交换基准数到中间
    if (begin < part - 1) quickSort(begin, part);
    if (part + 1 < end - 1) quickSort(part + 1, end);
}