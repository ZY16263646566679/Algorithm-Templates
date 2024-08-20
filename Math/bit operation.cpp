#include <bits/stdc++.h>
using namespace std;

// 判断是否是2的幂
#define isPower(x) (x && !(x & x - 1))

// 消除二进制最后一个1
int kk = kk & (kk - 1);

// 直接获取二进制中1的个数
int __builtin_popcount(unsigned);

// 获取前导零的个数
int __builtin_clz(unsigned);

// 获取末尾零的个数
int __builtin_ctz(unsigned);

// 最小元素
#define lowbit(x) ((x) & -(x))