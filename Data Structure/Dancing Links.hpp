#include <bits/stdc++.h>
using namespace std;

struct node { // 节点
    int u, d, l, r; // 上下左右
    int row, col; // 行列（从一开始）
};

int m, n, row[510], ccnt[510], cnt, ans[510]; // 行，列，每行第一个元素，每一列元素的个数，总节点个数
node links[6000]; // 舞蹈链中的所有元素（用下标来区分不同节点）

void init() {
    for (int i = 0; i <= n; i++) {
        links[i].l = i - 1;
        links[i].r = i + 1;
        links[i].u = i;
        links[i].d = i;
        ccnt[i] = 0;
    }
    links[0].l = n;
    links[n].r = 0;
    cnt = n;
}

void addnode(int r, int c) {
    links[++cnt].row = r;
    links[cnt].col = c;
    links[cnt].u = links[c].u; // 该列的最后一个节点
    links[cnt].d = c;
    links[links[cnt].u].d = cnt;
    links[c].u = cnt;
    if (!row[r]) {
        links[cnt].l = cnt;
        links[cnt].r = cnt;
        row[r] = cnt;
    } else {
        links[cnt].l = links[row[r]].l;
        links[cnt].r = row[r];
        links[links[row[r]].l].r = cnt;
        links[row[r]].l = cnt;
    }
    ccnt[c]++; // 列元素数加一
}

void remove(int x) { // 删除列元素所在列链中的元素及所对应行
    for (int i = links[x].d; i != x; i = links[i].d) // 删除列链中除了x外其它元素所在行中除了自己以外的元素
        for (int j = links[i].r; j != i; j = links[j].r) {
            links[links[j].u].d = links[j].d;
            links[links[j].d].u = links[j].u;
            ccnt[links[j].col]--;
        }
    // 删除列链
    links[links[x].l].r = links[x].r;
    links[links[x].r].l = links[x].l;
}

void resume(int x) { // 恢复
    links[links[x].l].r = x;
    links[links[x].r].l = x;
    for (int i = links[x].d; i != x; i = links[i].d)
        for (int j = links[i].r; j != i; j = links[j].r) {
            links[links[j].u].d = j;
            links[links[j].d].u = j;
            ccnt[links[j].col]++;
        }
}

bool dance(int deph) {
    if (links[0].r == 0) { // head.r = head，说明有解
        for (int i = 1; i < deph; i++) cout << ans[i] << ' ';
        cout << endl;
        return true;
    }
    int x = links[0].r;
    for (int i = links[x].r; i; i = links[i].r) if (ccnt[i] < ccnt[x]) x = i; // 选取列链最短的一条开始
    remove(x);
    for(int i = links[x].d; i != x; i = links[i].d) { //枚举选择行
        ans[deph] = links[i].row;
        for(int j = links[i].r; j != i; j = links[j].r) //删除选择行链元素所在列链
            remove(links[j].col);
        if(dance(deph + 1) ) return true;
        for(int j = links[i].r; j != i; j = links[j].r) //恢复选择行链元素所在列链
            resume(links[j].col);
    }
    resume(x); //恢复列链
    return false;
}
