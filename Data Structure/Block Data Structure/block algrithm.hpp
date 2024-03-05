#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, a[N]; // 下标从0开始
/**
 * size_：块的大小，m：块的数量
 * pos[i]：a[i] 所在块的标号
 * st/ed[i]：第 i 的块的开始和结束位置
 */
int size_, m, pos[N], st[N], ed[N];

void init() {
    size_ = sqrt(n);
    m = (n + size_ - 1) / size_;
    for (int i = 0; i < n; i++)
        pos[i] = i / size_;
    for (int i = 0; i < m; i++) {
        st[i] = i * size_;
        ed[i] = i * size_ + size_ - 1;
    }
    ed[m - 1] = n - 1;
}

// sum[i]：第 i 个块的区间和
int sum[N], add[N];

void init_sum() {
    for (int i = 0; i < m; i++)
        for (int j = st[i]; j <= ed[i]; j++)
            sum[i] += a[j];
}

// 让 [l, r] 内的每个元素加 d
void update(int l, int r, int d) {
    int p = pos[l], q = pos[r];
    if (p == q) {
        for (int i = l; i <= r; i++) a[i] += d;
        sum[p] += d * (r - l + 1);
        return;
    }
    for (int i = l; i <= ed[p]; i++) a[i] += d;
    sum[p] += d * (ed[p] - l + 1);
    for (int i = p + 1; i <= q - 1; i++) add[i] += d;
    for (int i = st[q]; i <= r; i++) a[i] += d;
    sum[q] += d * (r - st[q] + 1);
}

// 查询 [l, r] 内每个元素的和
int query(int l, int r) {
    int p = pos[l], q = pos[r], res = 0;
    if (p == q) {
        for (int i = l; i <= r; i++) res += a[i];
        return res;
    }
    res = add[p] * (ed[p] - l + 1) + add[q] * (r - st[q] + 1);
    for (int i = l; i <= ed[p]; i++) res += a[i];
    for (int i = p + 1; i < q - 1; i++) res += sum[i];
    for (int i = st[q]; i <= r; i++) res += a[i];
    return res;
}