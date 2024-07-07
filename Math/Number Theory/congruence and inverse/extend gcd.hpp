#include <bits/stdc++.h>
using namespace std;

/**
 * 扩展 gcd，返回 (a, b)
 *
 * 证明：
 * ∵ ax + by = (a, b) = (b, a % b) = bx' + (a % b)y'
 * ∴ a % b = a - [a / b] * b
 * ∴ ax + by = bx' + (a - ⌊a / b⌋ * b)y'
 *  = ay' + b(x' - ⌊a / b⌋ * y')
 * ∴ x = y', y = x' - ⌊a / b⌋ * y'
 *
 * 用途：
 * 1. 用于解二元不定方程 ax + by = (a, b)
 * 特解为 x0，y0，通解为 x0 + kb / (a, b), y0 - ka / (a, b)，k 为整数
 * 2. 用于求逆元
 * ax ≡ 1(mod m) <=> ax + my = 1（m -> b）
 * 特解是 x0，通解是 x0 + km，k 为整数
 */

// 递归版本
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 非递归版本
int exgcd(int a, int b, int& x, int& y) {
    int m = 0, n = 1;
    x = 1; y = 0;
    while (b) {
        int d = a / b, t;
        t = m; m = x - d * t; x = t;
        t = n; n = y - d * t; y = t;
        t = a % b; a = b; b = t;
    }
    return a;
}