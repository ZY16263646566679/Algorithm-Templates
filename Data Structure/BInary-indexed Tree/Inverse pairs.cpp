// 树状数组求逆序对（i < j, a[i] > a[j]）
#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x & -x)

const int N = 1e5 + 10;
// n：元素个数，m：去重后元素个数，数组下标从1开始
int n, a[N], t[N];

// 树状数组求和函数
int query(int i) { // 返回前i个元素的和
    int sum = 0;
    while (i) {
        sum += t[i];
        i -= lowbit(i);
    }
    return sum;
}

// 树状数组更新函数
void update(int i, int val) {
    while (i <= n) {
        t[i] += val;
        i += lowbit(i);
    }
}

// 求逆序对函数
int sortedIndexs[N]; // 下标数组
int inversePairs() {
    iota(sortedIndexs, sortedIndexs + n, 1); // 下标从1开始
    sort(sortedIndexs, sortedIndexs + n, [&](int i, int j) {
        if (a[i] == a[j]) return i > j; // 元素相等时，按下标逆序（这样可以避免元素值一样时，被算进逆序对数量里面）
        return a[i] > a[j]; // 元素不相等时，按元素逆序
    });
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += query(sortedIndexs[i]); // 查询大于自己的元素中有多少元素的下标小于自己
        update(sortedIndexs[i], 1);
    }
    return count;
}
