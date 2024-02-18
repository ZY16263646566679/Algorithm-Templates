// 只能用于元素互不相同。从0开始，0是顺序，n! - 1是逆序
#include <bits/stdc++.h>
using namespace std;

int fact[13] { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600 };

// 康托展开
int cantor(vector<int> nums) {
    int n = nums.size(), res = 0;
    for (int i = 0; i < n; i++) {
        int smaller = 0;
        for (int j = i + 1; j < n; j++)
            if (nums[j] < nums[i])
                smaller++;
        res += smaller * fact[n - i - 1];
    }
    return res;
}

// 逆康托展开（第k个全排列）
vector<int> getPermutation(vector<int> nums, int k) {
    set<int> s(nums.begin(), nums.end());
    int n = nums.size();
    vector<int> res;
    while (n) {
        auto it = s.begin();
        while (k > fact[n - 1]) k -= fact[n - 1], it++;
        res.push_back(*it);
        s.erase(it);
        n--;
    }
    return res;
}