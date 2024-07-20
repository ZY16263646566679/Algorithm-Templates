#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
int randint(long long a, long long b) { // 区间[a, b]内随机数
    // static mt19937_64 m;
    random_device rd;
    return rd() % (b - a + 1) + a;
}