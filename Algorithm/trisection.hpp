// 三分法求极值（极大值）
#include <bits/extc++.h>
using namespace std;

// 实数三分
double calc(double l, double r, function<double(double)> f) {
    while (r - l > 1e-5) {
        double mid1 = l + (r - l) / 3, res1 = f(mid1);
        double mid2 = r - (r - l) / 3, res2 = f(mid2);
        if (res1 < res2) l = mid1;
        else if (res1 > res2) r = mid2;
        else l = mid1, r = mid2;
    }
    return f((l + r) / 2);
}

// 整数三分
int calc(int l, int r, function<int(int)> f) {
    while (r - l > 2) {
        int mid1 = l + (r - l) / 3, res1 = f(mid1);
        int mid2 = r - (r - l) / 3, res2 = f(mid2);
        if (res1 < res2) l = mid1;
        else if (res1 > res2) r = mid2;
        else l = mid1, r = mid2;
    }
    return max(f(l + 1), max(f(l), f(r)));
}