// 双向动态链表，要注意内存管理
#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    node* pre, * next;
}* head, * tail; // 链表的头和尾

int cnt; // 节点个数

void init(int val) {
    head = new node{val, nullptr, nullptr};
    tail = head;
    cnt++;
}

void add(int val) {
    node* x = new node{val, tail, head};
    tail->next = x;
    tail = tail->next;
    head->pre = x;
    cnt++;
}


void remove(node* x) {
    x->pre->next = x->next;
    x->next->pre = x->pre;
    delete x;
    cnt--;
}

// 循环链表
void init(int val) {
    head = new node{val, head, head};
    tail = head;
    cnt++;
}
void add(int val) {
    node x({val, tail, head});
    tail->next = &x;
    tail = tail->next;
    head->pre = &x;
    cnt++;
}