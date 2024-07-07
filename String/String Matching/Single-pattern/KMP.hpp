// 字符串匹配之KMP算法
#include <bits/stdc++.h>
using namespace std;

/**
 * Next[j]：以下标为j的字符结尾的前缀字符串的最大公共前后缀字符串长（前后缀字符串长度不能等于j + 1）
 * 也就是可以跳过的字符数量
 * Next[j - 1]是s[i]和p[j]不相等时，新的j的位置
 * 该数组也可用于找所有的公共前后缀
 */
const int N = 1e6 + 5;
int Next[N];

/**
 * dp 法求所有前缀的最长公共前后缀
 * j 是上一个字符串的最长公共前后缀长，同时也是最长公共前后缀所对应的前缀的后一个字符的下标
 * 当p[j] != p[i]时，说明p[0..j]不是p[0..i]的最长公共前后缀
 * 又因为p[0..j-1]就是p[i-j..i-1]，所以p[0..i]的最长公共前后缀也是p[i-j..i]的最长公共前后缀
 * 也就是p[0..j-1] + p[i]的最长公共前后缀
 */
void getFail(string& p) {
    int plen = p.length();
    Next[0] = 0;
    for (int i = 1; i < plen; i++) {
        int j = Next[i - 1];
        while (j && p[j] != p[i]) j = Next[j - 1];
        Next[i] = p[i] == p[j] ? j + 1 : 0;
    }
}

int kmp(string& s, string& p) {
    int cnt = 0;
    int slen = s.length(), plen = p.length();
    getFail(p);
    int j = 0;
    for (int i = 0; i < slen; i++) {
        while (j && s[i] != p[j]) j = Next[j - 1];
        if (s[i] == p[j]) j++;
        if (j == plen) { // 找到了
            cnt++;
            cout << i - j + 1 << ' '; // 在s中匹配到p的开始的下标
            j = Next[j - 1]; // 继续匹配
        }
    }
    return cnt;
}