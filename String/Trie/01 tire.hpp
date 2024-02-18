// 01字典树用于求解异或最值问题
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int son[N][2], idx, num[N]; // idx为0的节点为根节点
void insert(int x){
    int p = 0;
    for(int i = 30; ~i; i--) {
        int u = x >> i & 1; //判断x这个数的第i位上的数是1还是0
        if(!num[son[p][u]]) son[p][u] = ++idx;
        num[son[p][u]]++;
        p = son[p][u];
    }
}
void erase(int x) {
    int p = 0;
    for (int i = 30; ~i; i--) {
        int u = x >> i & 1;
        num[son[p][u]]--;
        p = son[p][u];
    }
}
int query(int x) {
    int p = 0, res = 0;
    for(int i = 30; ~i; i--) {
        int u = x >> i & 1;
        if (num[son[p][!u]]) {
            res += 1 << i;
            p = son[p][!u];
        } else p = son[p][u];
    }
    return res;
}