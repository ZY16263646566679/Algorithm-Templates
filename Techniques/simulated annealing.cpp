// 模拟退火
#include <bits/stdc++.h>
using namespace std;

// 例题链接：https://www.luogu.com.cn/problem/P1337
const int N = 1e4 + 5;
int n, x[N], y[N], w[N];
double ansx, ansy, dis;

#define Rand() (1.0 * rand() / RAND_MAX)

double calc(double xx, double yy) {
    double res = 0;
    for (int i = 1; i <= n; i++) {
        double dx = x[i] - xx, dy = y[i] - yy;
        res += sqrt(dx * dx + dy * dy) * w[i];
    }
    if (res < dis) dis = res, ansx = xx, ansy = yy;
    return res;
}

void simulateAnneal() {
    double t = 1e12;
    for (double nowx = ansx, nowy = ansy; t > 1e-3; t *= 0.99) {
        double nxtx = nowx + t * (Rand() * 2 - 1);
        double nxty = nowy + t * (Rand() * 2 - 1);
        double delta = calc(nxtx, nxty) - calc(nowx, nowy);
        if (exp(-delta / t) > Rand())
            nowx = nxtx, nowy = nxty;
    }
    for (int _ = 1000; _--;) {
        double nxtx = ansx + t * (Rand() * 2 - 1);
        double nxty = ansy + t * (Rand() * 2 - 1);
        calc(nxtx, nxty);
    }
}

void solve() {
    srand(0);
    for (int _ = 8; _--;) simulateAnneal();
}