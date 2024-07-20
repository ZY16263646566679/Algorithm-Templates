// 双向静态链表
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
struct node {
    int id;
    int val;
    int pre, next;
} nodes[N]; // 节点下标从1开始

int n, cnt, head; // cnt：节点数，head：头节点
bool exist[N];

void init(int val) {
    head = cnt = 1;
    nodes[1].val = val;
    nodes[1].pre = 0; // 0表示头
    nodes[1].next = -1; // -1表示尾
    exist[1] = true;
}

void add(int val, int pre, int next) {
    nodes[++cnt] = {cnt, val, pre, next};
    if (pre) nodes[pre].next = cnt;
    if (~next) nodes[next].pre = cnt;
    if (pre == 0) head = cnt;
    exist[cnt] = true;
}

void remove(int id) {
    nodes[nodes[id].pre].next = nodes[id].next;
    nodes[nodes[id].next].pre = nodes[id].pre;
    exist[id] = false;
    cnt--;
}

void traverse() { // 遍历
    for (int i = head; ~i; i = nodes[i].next) {
        // 操作
        cout << nodes[i].val << ' ';
    }
}
