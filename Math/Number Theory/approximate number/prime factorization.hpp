// 分解质因数
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int p[N];

int getPrime(int n) { // 返回不同质因数个数
    int k = 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            p[k++] = i;
            while (n % i == 0) n /= i;
        }
    if (n != 1) p[k++] = n;
    return k;
}

// 统计个数
map<int, int> primeFactorization(int n) {
    map<int, int> res;
    for (int i = 2; i * i <= n; i++)
        while (n % i == 0) {
            res[i]++;
            n /= i;
        }
    if (n > 1) res[n]++;
    return res;
}