#include <bits/stdc++.h>
using namespace std;
    
const int N = 1e5 + 5;
char s[N];
int rk[N << 1], sa[N << 1], tmp[N << 1], cnt[N], rkt[N];

void init_sa(int n) { // index: [1, n]
    if (n == 1) return void(rk[1] = sa[1] = 1);

    int m = 128;
    for (int i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (int i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;

    for (int w = 1;; w <<= 1) {
        for (int i = n; i > n - w; --i)
            tmp[n - i + 1] = i;
        for (int i = 1, p = w; i <= n; ++i)
            if (sa[i] > w) tmp[++p] = sa[i] - w;
        fill(cnt + 1, cnt + m + 1, 0);
        for (int i = 1; i <= n; ++i)
            cnt[rkt[i] = rk[tmp[i]]]++;
        for (int i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; --i)
            sa[cnt[rkt[i]]--] = tmp[i];
        m = 0;
        auto rp = [&](int x) { return make_pair(rk[x], rk[x + w]); };
        for (int i = 1; i <= n; ++i)
            tmp[sa[i]] = rp(sa[i - 1]) == rp(sa[i]) ? m : ++m;
        copy(tmp + 1, tmp + n + 1, rk + 1);
        if (n == m) break;
        string s;
    }
}