#include <bits/stdc++.h>
using namespace std;

// 多项式
namespace Polynomial {
    struct monomial { // ax^b
        int a, b;
        monomial to_dif() { // 求导
            if (b == 0) return { 0, 0 };
            return { a * b, b - 1 };
        }
        string toString() {
            if (a > 1) {
                if (b > 1) return to_string(a) + "x^" + to_string(b);
                if (b == 1) return to_string(a) + "x";
                if (b == 0) return to_string(a);
            }
            if (a == 1) {
                if (b > 1) return "x^" + to_string(b);
                if (b == 1) return "x";
                if (b == 0) return "1";
            }
            if (a == 0) return "0";
            return "-1";
        }
    };
    monomial toMono(string s) { // 不可以是+-x^b的形式
        int len = s.length();
        if (s[0] != 'x') {
            int j = 0;
            while (s[++j] != 'x' && j < len);
            if (j < len - 1) return { stoi(string(s.begin(), s.end() + j)), stoi(string(s.begin() + j + 2, s.end())) };
            if (j == len - 1) return { stoi(string(s.begin(), s.end() - 1)), 1 };
            return { stoi(string(s.begin(), s.end())), 0 };
        }
        if (len > 1) return { 1, stoi(string(s.begin() + 2, s.end())) };
        return { 1, 1 };
    }
}

// 数论
namespace Number_theory {
    // 二进制gcd，只能处理自然数(大于等于的整数) 极特殊情况下会快于__gcd();
    unsigned long long binary_gcd(unsigned long long a, unsigned long long b) {
        if (a == 0 || b == 0) return a + b;
        if (a % b == 0) return b;
        if (a > b) {
            if (a & 1)
                if (b & 1) return binary_gcd(a - b >> 1, b);
                else return binary_gcd(a, b >> 1);
            else
                if (b & 1) return binary_gcd(a >> 1, b);
                else return binary_gcd(a >> 1, b >> 1) << 1;
        } else {
            if (b & 1)
                if (a & 1) return binary_gcd(b - a >> 1, a);
                else return binary_gcd(b, a >> 1);
            else
                if (a & 1) return binary_gcd(b >> 1, a);
                else return binary_gcd(b >> 1, a >> 1) << 1;
        }
    }
}
