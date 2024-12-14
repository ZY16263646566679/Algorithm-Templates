// 约数个数
#include <bits/stdc++.h>
using namespace std;

/**
 * 约数个数定理：
 * https://baike.baidu.com/item/%E7%BA%A6%E6%95%B0%E4%B8%AA%E6%95%B0%E5%AE%9A%E7%90%86/4926961
 */

int getNum(int n) {
    map<int, int> cnt;
    for (int i = 2; i * i <= n; i++)
        while (n % i == 0) {
            n /= i;
            cnt[i]++;
        }
    if (n > 1) cnt[n]++;
    int ans = 1;
    for (auto& [_ , c] : cnt) ans *= c + 1;
    return ans;
}