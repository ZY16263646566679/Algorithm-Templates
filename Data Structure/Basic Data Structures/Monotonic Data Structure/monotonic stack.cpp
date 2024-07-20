// 单调栈
#include <bits/stdc++.h>
using namespace std;

stack<int> st;

void add(int x) { // 栈顶->栈底：小->大
    while (!st.empty() && st.top() <= x) st.pop();
    st.push(x);
}

int find() {
    return st.top();
}

// 静态数组模拟栈，效率更高
const int N = 1e6 + 5;
int stk[N], top;

void add(int x) {
    while (top && stk[top - 1] <= x) top--;
    stk[top++] = x;
}

int find() {
    return stk[top - 1];
}