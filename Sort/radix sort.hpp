// 基数排序，只能用于元素都是非负数
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;
int a[N], t[N];
void radixsort(int l, int r) {  // 将[l, r)内元素升序排序
    int maxe = *max_element(a + l, a + r), d = 0; // 数组中的最大值和位数
    while (maxe) maxe /= 10, d++;
    int radix = 1, cnt[10] {};
    while (d--) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = l, k; i < r; i++) {
            k = a[i] / radix % 10;
            cnt[k]++;
        }
        for (int i = 1; i < 10; i++) cnt[i] += cnt[i - 1]; // 排序后每个基数对应的位置
        for (int i = r - 1; i >= l; i--) {
            int k = a[i] / radix % 10;
            t[l + cnt[k] - 1] = a[i]; // 注意减一才是下标
            cnt[k]--; // 下一个的下标减一
        }
        for (int i = l; i < r; i++) a[i] = t[i];
        radix *= 10;
    }
}

// 如果需要降序排序，最后再逆序一下即可