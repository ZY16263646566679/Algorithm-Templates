// 缩点
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, sccno[N], cnt; // 每个点所属的SCC编号，SCC的个数
vector<int> e[N], ne[N];

// 此处略去求SCC的算法……

void condensation() {
    for (int i = 1; i <= n; i++)
        for (int v : e[i])
            if (sccno[i] - sccno[v])
                ne[sccno[i]].push_back(sccno[v]);
}