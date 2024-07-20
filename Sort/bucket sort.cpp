// 桶排序
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, a[N];
void bucketSort(int l, int r) {
    int Min = *min_element(a + l, a + r), Max = *max_element(a + l, a + r), capacity = (Max - Min) / 100;
    vector<vector<int>> bucket(101);
    for (int i = l; i <= r; i++)
        bucket[(a[i] - Min) / capacity].push_back(a[i]);
    for (int i = 0, index = l; i <= 100; i++) {
        if (bucket[i].size() == 0) continue;
        sort(bucket[i].begin(), bucket[i].end());
        int quantity = bucket[i].end() - bucket[i].begin();
        for (int j = 0; j < quantity; j++)
            a[index++] = bucket[i][j];
    }
}