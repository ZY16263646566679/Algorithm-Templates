// 三大简单排序
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6;
int a[maxn + 1];
// 对[l, r], [begin, end)范围内元素升序排序
void simpleSort(int *begin, int *end) { // 比冒泡排序稍快
    int n = end - begin;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (begin[i] > begin[j]) { // 自己交换比用swap()函数快一点
                begin[i] ^= begin[j];
                begin[j] ^= begin[j];
                begin[i] ^= begin[j];
            }
}
void bubbleSort(int *begin, int *end) { // 最慢
    int n = end - begin;
    for (int i = n - 1; i >= 1; i--)
        for (int j = 0; j < i; j++)
            if (begin[j] > begin[j + 1])
            {
                begin[j] ^= begin[j + 1];
                begin[j + 1] ^= begin[j];
                begin[j] ^= begin[j + 1];
            }
}
void selectSort(int *begin, int *end) { // 时间复杂度O(n²)的算法中最快的
    int n = end - begin;
    for (int i = n - 1, Max = 0; i >= 1; i--)
    {
        for (int j = 0; j <= i; j++)
            if (begin[j] > begin[Max])
                Max = j;
        begin[Max] ^= begin[i];
        begin[i] ^= begin[Max];
        begin[Max] ^= begin[i];
        Max = 0;
    }
}

float print_time(void fun(int, int)) { // 输出排序时间
    clock_t begin, end;
    for (int i = 1; i <= maxn; i++) // 检查数组元素数最大时运行时间
        a[i] = rand();              // 产生short型随机数
    // default_random_engine engine;       // 产生int型随机数
    // for (int i = 1; i <= maxn; i++)
    //     a[i] = engine();
    begin = clock();
    fun(1, maxn);
    end = clock();
    if (is_sorted(a + 1, a + 1 + maxn))
        return 1.0 * (end - begin) / CLOCKS_PER_SEC;
    else
        return -1;
}