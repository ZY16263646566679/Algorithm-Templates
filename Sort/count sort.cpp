// 计数排序，只能用于数据范围比较小的数组（不超过1e7）但是排序速度极快，复杂度为O(n)
#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;
int n, a[N], cnt[N];

void countSort(int* begin, int* end) {
    int Min = *min_element(begin, end), Max = *max_element(begin, end);
    if (Max - Min + 1 > 1e7) {
        cout << "范围过大" << endl;
        return;
    }
    int n = end - begin;
    for (int i = 0; i < n; i++)
        cnt[begin[i] - Min]++;
    for (int i = 0, index = 0; i <= Max - Min; i++)
        for (int j = 0; j < cnt[i]; j++)
            begin[index++] = i + Min;
}

// 如果需要降序排序，最后再逆序一下或者将最后的for循环的外层换成逆序即可