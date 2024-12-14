#include <bits/stdc++.h>
using namespace std;

// 最大公约数
int gcd(int a, int b) { // 递归版
    if (!a || !b) return a + b;
    return gcd(b, a % b);
}

int gcd(int a, int b) { // 非递归版
    while (b) {
        int t = a % b;
        a = b, b = t;
    }
    return a;
}

// 也可以用库函数__gcd()和gcd()，前者只能用于非负数

// 最小公倍数
int lcm(int a, int b) {
    return a / gcd(a, b) * b; // 先除后乘防止溢出
}