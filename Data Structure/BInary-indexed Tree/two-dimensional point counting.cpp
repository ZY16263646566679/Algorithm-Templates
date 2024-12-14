#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
/**
 * c：操作数量
 * op[]：操作数组
 * ny[]：y 坐标数组
 * k：y 坐标数量
 * ans[]：答案数组
 */
int n, m, c, ans[N];
int ny[N * 3], k, t[N * 3];

struct {
    // t：-1 查询删除，1 查询添加，0 加点
    int i, x, y, t;
    bool operator<(auto& o) {
        if (x == o.x) // 坐标相同时，先加点，再查询
            return !t;
        return x < o.x;
    }
} op[N * 5];

#define lb(x) (x & -x)

void add(int x) {
    for (; x <= k; x += lb(x))
        t[x]++;
}

int sum(int x) {
    int res = 0;
    for (; x; x -= lb(x))
        res += t[x];
    return res;
}

void solve() {
    cin >> n >> m;
    for (int x, y, i = n; i--;) {
        cin >> x >> y;
        op[c++] = {0, x, y, 0};
        ny[k++] = y;
    }
    for (int a, b, c, d, i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        op[c++] = {i, a - 1, b - 1, 1};
        op[c++] = {i, a - 1, d, -1};
        op[c++] = {i, c, b - 1, -1};
        op[c++] = {i, c, d, 1};
        ny[k++] = b - 1, ny[k++] = d;
    }
    sort(ny, ny + k); // 离散化
    k = unique(ny, ny + k) - ny;
    sort(op, op + c);
    for (int _ = 0; _ < c; _++) {
        auto [i, x, y, t] = op[_];
        int p = lower_bound(ny, ny + k, y) - ny + 1;
        if (!t) add(p);
        if (t < 0) ans[i] -= sum(p);
        if (t > 0) ans[i] += sum(p);
    }
}