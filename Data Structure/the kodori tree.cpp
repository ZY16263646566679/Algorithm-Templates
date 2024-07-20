// 珂朵莉树
#include <bits/stdc++.h>
using namespace std;

class RangeModule { // range模块，[left, right)
    map<int, int> range;
public:
    RangeModule() {}
    
    void addRange(int left, int right) {
        auto r = range.lower_bound(left);
        if (r != range.begin()) {
            auto l = prev(r);
            if (l->second >= right) return;
            if (l->second >= left) {
                left = l->first;
                range.erase(l);
            }
        }
        while (r != range.end() && r->first <= right) {
            if (r->second > right) right = r->second;
            r = range.erase(r);
        }
        range[left] = right;
    }
    
    bool queryRange(int left, int right) {
        auto it = range.upper_bound(left);
        if (it == range.begin()) return false;
        it = prev(it);
        return right <= it->second;
    }
    
    void removeRange(int left, int right) {
        auto r = range.upper_bound(left);
        if (r != range.begin()) {
            auto l = prev(r);
            if (l->second >= right) {
                int ri = l->second;
                if (l->first == left) range.erase(l);
                else l->second = left;
                if (right != ri) range[right] = ri;
                return;
            } else if (l->second > left) {
                if (l->first == left) range.erase(l);
                else l->second = left;
            }
        }
        while (r != range.end() && r->first < right) {
            if (r->second <= right) r = range.erase(r);
            else {
                range[right] = r->second;
                range.erase(r);
                break;
            }
        }
    }
};

// 也可以用set实现
struct node {
    int l, r;
    mutable int v; // 区间值
    bool operator<(const node& rhs) const { return l < rhs.l; }
};

set<node> odt;