// 对顶堆
#include <bits/stdc++.h>
using namespace std;

// 动态求中位数
class DualHeap {
private:
    int smallSize = 0, largeSize = 0; // smallSize >= largeSize
    priority_queue<int> small; // small one
    priority_queue<int, vector<int>, greater<>> large; // big one
    unordered_map<int, int> delayed; // delay delete;

    template<typename T>
    void prune(T& heap) { // 使堆顶不为待删除元素
        while (!heap.empty()) {
            int num = heap.top();
            if (delayed.count(num)) {
                --delayed[num];
                if (!delayed[num])
                    delayed.erase(num);
                heap.pop();
            } else break;
        }
    }

    void makeBalance() {
        if (smallSize > largeSize + 1) {
            large.push(small.top());
            small.pop();
            --smallSize;
            ++largeSize;
            prune(small);
        } else if (smallSize < largeSize) {
            small.push(large.top());
            large.pop();
            ++smallSize;
            --largeSize;
            prune(large);
        }
    }
public:
    DualHeap() {}

    void insert(int num) {
        if (small.empty() || num <= small.top()) {
            small.push(num);
            ++smallSize;
        } else {
            large.push(num);
            ++largeSize;
        }
        makeBalance();
    }

    void erase(int num) {
        ++delayed[num];
        if (num <= small.top()) {
            --smallSize;
            if (num == small.top()) prune(small);
        } else {
            --largeSize;
            if (num == large.top()) prune(large);
        }
        makeBalance();
    }

    double getMedian() {
        return (smallSize + largeSize) & 1 ? small.top() : (small.top() + large.top()) / 2.0;
    }
};

// 求第 k 大元素 / 前 k 大元素和
class DualHeap {
private:
    int smallSize = 0, largeSize = 0, k, sum = 0; // smallSize >= largeSize
    priority_queue<int> small; // small one
    priority_queue<int, vector<int>, greater<>> large; // big one
    unordered_map<int, int> delayed; // delay delete;

    template<typename T>
    void prune(T& heap) {
        while (!heap.empty()) {
            int num = heap.top();
            if (delayed.count(num)) {
                --delayed[num];
                if (!delayed[num])
                    delayed.erase(num);
                heap.pop();
            } else break;
        }
    }

    void makeBalance() {
        if (smallSize > k) {
            sum -= small.top();
            large.push(small.top());
            small.pop();
            --smallSize;
            ++largeSize;
            prune(small);
        } else if (largeSize && smallSize < k) {
            sum += large.top();
            small.push(large.top());
            large.pop();
            ++smallSize;
            --largeSize;
            prune(large);
        }
    }
public:
    DualHeap() {}
    DualHeap(int k) : k(k) {}

    void insert(int num) {
        if (small.empty() || num <= small.top()) {
            small.push(num);
            sum += num;
            ++smallSize;
        } else {
            large.push(num);
            ++largeSize;
        }
        makeBalance();
    }

    void erase(int num) {
        ++delayed[num];
        if (num <= small.top()) {
            --smallSize;
            sum -= num;
            if (num == small.top()) prune(small);
        } else {
            --largeSize;
            if (num == large.top()) prune(large);
        }
        makeBalance();
    }

    int getKth() { // 获取第 k 大元素
        return small.top();
    }

    int getSum() { // 前 k 大元素和
        return sum;
    }
};