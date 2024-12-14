// 约数和
#include <bits/stdc++.h>
using namespace std;

/**
 * 约数和定理：
 * https://baike.baidu.com/item/%E7%BA%A6%E6%95%B0%E5%92%8C%E5%AE%9A%E7%90%86/3808428
 */

int getSum(int n) {
    map<int, int> cnt;
    for (int i = 2; i * i <= n; i++)
        while (n % i == 0) {
            n /= i;
            cnt[i]++;
        }
    if (n > 1) cnt[n]++;
    int ans = 1;
    for (auto& [x, c] : cnt)
        ans *= ((int)pow(x, c + 1) - 1) / (x - 1);
    return ans;
}