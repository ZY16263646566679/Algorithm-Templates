/**
 * k叉哈夫曼树
 * 每一次合并会减少k - 1个节点
 * 如果n - 1不是k - 1的倍数，那么最后根节点会有空儿子，不是最优
 * 需要加入新节点保证最优
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
    ll w, h; // w：权值，h：高度（用来保证树的高度最小）
    bool operator<(const node &a) const { return a.w == w ? h > a.h : w > a.w; }
};

const int N = 1e5 + 5;
// n：种类数，k：进制数，p[]：使用频数，wpl：树的带权路径长度
ll n, k, p[N], wpl;
priority_queue<node> q;

void init() {
    for (int i = 1; i <= n ; i++)
        q.push({p[i], 1});
    int cnt = (n - 1) % (k - 1) ? k - 1 - (n - 1) % (k - 1) : 0;
    while (cnt--) // 加入0节点来保证最优
        q.push({0, 1});
}

void build() {
    while (q.size() >= k) {
        ll h = 0, w = 0; // h：最大高度，w：权值和
        for (int i = 0; i < k; i++) {
            node t = q.top();
            q.pop();
            if (t.h > h) h = t.h;
            w += t.w;
        }
        wpl += w;
        q.push({w, h + 1});
    }
}