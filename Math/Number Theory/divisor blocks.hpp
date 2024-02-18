// 整除分块（数论分块，时间复杂度O(√n)）用以解决∑(n/i)的问题（1 <= i <= n）
#include <iostream>
using namespace std;
using ll = long long;

ll calc(ll n) {
    ll sum = 0;
    ll l = 1, r; // l为左端点，r为右端点，n/l为分块内的值
    while (l <= n) {
        r = n / (n / l); // 块的右端点（可以代入几个数据验证试试）
        sum += (r - l + 1) * (n / l); // 块的大小（长度）乘以分块内的值
        l = r + 1; // 新的左端点
    }
    return sum;
}