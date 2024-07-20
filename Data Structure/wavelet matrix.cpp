#include <bits/stdc++.h>
using namespace std;

struct indexable_bit_array {
    int n, blocks;
    vector<uint64_t> bits;
    vector<int> prefix_sum;

    indexable_bit_array(int _n = 0) : n(_n) {
        blocks = (n + 63) / 64;
        bits.assign(blocks, 0);
        prefix_sum.assign(blocks + 1, 0);
    }

    void set(int k) {
        bits[k / 64] |= 1LLU << (k & 63);
    }

    void build() {
        prefix_sum[0] = 0;

        for (int i = 0; i < blocks; i++)
            prefix_sum[i + 1] = prefix_sum[i] + __builtin_popcountll(bits[i]);
    }

    bool operator[](int k) const {
        return bits[k / 64] >> (k & 63) & 1;
    }

    int rank(int k) const {
        return prefix_sum[k / 64] + __builtin_popcountll(bits[k / 64] & ((1LLU << (k & 63)) - 1));
    }

    // Count how many 1's / 0's are in indices [0, k)
    int rank(bool val, int k) const {
        return val ? rank(k) : k - rank(k);
    }

    // Find the k-th 1 / k-th 0 in the array
    int search(bool val, int k) const {
        if (k < 0)
            return -1;

        if (k >= rank(val, n))
            return n;

        int low = 0, high = n - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (rank(val, mid) < k)
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }

    // Find the k-th 1 / k-th 0 in the array starting at start
    int search(bool val, int k, int start) const {
        return search(val, k + rank(val, start));
    }
};

/**
 * wavelet_matrix takes an array v and preprocesses the data in O(n log n) to answer the following queries in O(log n):
 * 1) count v[i] = x for i in [start, end)
 * 2) count v[i] < upper for i in [start, end)
 * 3) find the k-th smallest / k-th largest v[i] for i in [start, end), k in [0, end - start)
 * 4) find the smallest value >= lower / largest value < upper for i in [start, end)
 */
template<typename T>
struct wavelet_matrix {
    int n, levels; // n: size of v and wm
    bool needs_compression = false;
    vector<T> sorted;
    vector<indexable_bit_array> matrix;
    vector<int> mid;

    wavelet_matrix(const vector<T> &v = {}, bool _needs_compression = false) {
        build(v, _needs_compression);
    }

    int compress_value(T x) const {
        return int(lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin());
    }

    void build(vector<T> v, bool _needs_compression) {
        n = int(v.size());
        needs_compression = _needs_compression;

        if (needs_compression) {
            vector<pair<T, int>> pairs(n);

            for (int i = 0; i < n; i++)
                pairs[i] = {v[i], i};

            sort(pairs.begin(), pairs.end(), [](const pair<T, int> &x, const pair<T, int> &y) -> bool {
                return x.first < y.first;
            });

            sorted.clear();
            int current = 0;

            for (int i = 0, j = 0; i < n; i = j) {
                while (j < n && pairs[i].first == pairs[j].first)
                    v[pairs[j++].second] = current;

                sorted.push_back(pairs[i].first);
                current++;
            }
        }

        assert(all_of(v.begin(), v.end(), [](T x) -> bool { return x >= 0; }));

        if (n == 0) {
            levels = 0;
            matrix.clear();
            mid.clear();
            return;
        }

        T max_value = *max_element(v.begin(), v.end());
        levels = 0;

        while (T(1) << levels <= max_value)
            levels++;

        matrix.resize(levels);
        mid.resize(levels);

        for (int level = levels - 1; level >= 0; level--) {
            matrix[level] = indexable_bit_array(n + 1);
            vector<T> left, right;
            left.reserve(n); right.reserve(n);

            for (int i = 0; i < n; i++)
                if (v[i] >> level & 1) {
                    matrix[level].set(i);
                    right.push_back(v[i]);
                } else {
                    left.push_back(v[i]);
                }

            mid[level] = int(left.size());
            matrix[level].build();
            copy(left.begin(), left.end(), v.begin());
            copy(right.begin(), right.end(), v.begin() + left.size());
        }
    }

    // Given an index, find the corresponding index on the next level if we take a certain bit.
    int successor(int level, bool bit, int index) const {
        return bit * mid[level] + matrix[level].rank(bit, index);
    }

    // Compute v[k] in log time (??)
    T access(int k) const {
        T value = 0;

        for (int level = levels - 1; level >= 0; level--) {
            bool bit = matrix[level][k];

            if (bit)
                value |= T(1) << level;

            k = successor(level, bit, k);
        }

        return needs_compression ? sorted[value] : value;
    }

    // how many v[i] = x for i in [start, end)
    int rank(T x, int start, int end) const {
        if (needs_compression) {
            int index = compress_value(x);

            if (index >= int(sorted.size()) || sorted[index] != x)
                return 0;

            x = index;
        }

        if (x < 0 || x >= T(1) << levels)
            return 0;

        for (int level = levels - 1; level >= 0; level--) {
            bool bit = x >> level & 1;
            start = successor(level, bit, start);
            end = successor(level, bit, end);
        }

        return end - start;
    }

    // k-th smallest number in [start, end)
    T kth_smallest(int start, int end, int k) const {
        if (k < 0)
            return numeric_limits<T>::lowest();

        if (k >= end - start)
            return numeric_limits<T>::max();

        T value = 0;

        for (int level = levels - 1; level >= 0; level--) {
            int zero_count = matrix[level].rank(false, end) - matrix[level].rank(false, start);
            bool bit = k >= zero_count;

            if (bit) {
                value |= T(1) << level;
                k -= zero_count;
            }

            start = successor(level, bit, start);
            end = successor(level, bit, end);
        }

        return needs_compression ? sorted[value] : value;
    }

    // k-th largest number in [start, end)
    T kth_largest(int start, int end, int k) const {
        return kth_smallest(start, end, end - start - 1 - k);
    }

    // how many v[i] < upper for i in [start, end)
    int count_smaller(int start, int end, T upper) const {
        if (needs_compression)
            upper = compress_value(upper);

        if (upper >= T(1) << levels)
            return end - start;

        int count = 0;

        for (int level = levels - 1; level >= 0; level--) {
            bool bit = upper >> level & 1;

            if (bit)
                count += matrix[level].rank(false, end) - matrix[level].rank(false, start);

            start = successor(level, bit, start);
            end = successor(level, bit, end);
        }

        return count;
    }

    // how many lower <= v[i] < upper for i in [start, end)
    int count_range(int start, int end, T lower, T upper) const {
        return count_smaller(start, end, upper) - count_smaller(start, end, lower);
    }

    // max v[i] < upper for i in [start, end)
    T prev_value(int start, int end, T upper) const {
        int count = count_smaller(start, end, upper);
        return kth_smallest(start, end, count - 1);
    }

    // min v[i] >= lower for i in [start, end)
    T next_value(int start, int end, T lower) const {
        int count = count_smaller(start, end, lower);
        return kth_smallest(start, end, count);
    }
};