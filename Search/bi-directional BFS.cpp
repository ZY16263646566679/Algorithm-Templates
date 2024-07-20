// 双向广搜——双队列实现
#include <bits/stdc++.h>
using namespace std;

using str = string;

// 例题：https://www.luogu.com.cn/problem/P1032
int c1, c2; // 记录步数
queue<str> q1, q2;
set<str> vis1, vis2; // 记录是否访问过
map<str, vector<str>> e1, e2;

bool next(queue<str>& q, map<str, vector<str>>& e, set<str>& vis1, set<str>& vis2, int& c) {
    c++;
    for (int i = 0, n = q.size(); i < n; i++) {
        str s = q.front(); q.pop();
        for (auto& [k, v] : e) {
            if (k.length() > s.length()) continue;
            for (int j = 0; j <= s.length() - k.length(); j++) {
                if (s.substr(j, k.length()) != k) continue;
                for (str& x : v) {
                    str t = s;
                    t.replace(j, k.length(), x);
                    if (vis1.count(t)) continue;
                    if (vis2.count(t)) return true;
                    q.push(t), vis1.insert(t);
                }
            }
        }
    }
    return false;
}

int bfs(str a, str b) {
    q1.push(a), vis1.insert(a);
    q2.push(b), vis2.insert(b);
    while (q1.size() || q2.size()) {
        bool res;
        if (q1.size() && (q2.empty() || q2.size() >= q1.size()))
            res = next(q1, e1, vis1, vis2, c1);
        else res = next(q2, e2, vis2, vis1, c2);
        if (res) return c1 + c2;
    }
    return -1;
}