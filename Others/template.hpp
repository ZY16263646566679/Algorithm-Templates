#include <bits/stdc++.h>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef NEAL_DEBUG
#define dbg(...) cerr << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define FIO // 缓存模式 请勿在交互题开启
struct IO {
#ifdef FIO
    const static int BUFSIZE = 1 << 20;
    char buf[BUFSIZE], obuf[BUFSIZE], *p1, *p2, *pp;
    inline char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFSIZE, stdin), p1 == p2) ? EOF : *p1++); }
    inline void putchar(char x) { ((pp - obuf == BUFSIZE && (fwrite(obuf, 1, BUFSIZE, stdout), pp = obuf)), *pp = x, pp++); }
    inline IO &flush() {
        fwrite(obuf, 1, pp - obuf, stdout);
        fflush(stdout);
        return *this;
    }
    IO() { p1 = buf, p2 = buf, pp = obuf; }
    ~IO() { flush(); }
#else
    int (*getchar)() = &::getchar;
    int (*putchar)(int) = &::putchar;
    inline IO &flush()
    {
        fflush(stdout);
        return *this;
    };
#endif
    string sep = " ";
    int k = 2;
    template <typename Tp, typename std::enable_if<std::is_integral<Tp>::value || std::is_same<Tp, __int128_t>::value>::type * = nullptr>
    inline int read(Tp &s) {
        int f = 1;
        char ch = getchar();
        s = 0;
        while (!isdigit(ch) && ch != EOF)
            f = (ch == '-' ? -1 : 1), ch = getchar();
        while (isdigit(ch))
            s = s * 10 + (ch ^ 48), ch = getchar();
        s *= f;
        return ch != EOF;
    }
    template <typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>
    inline int read(Tp &s) {
        int f = 1;
        char ch = getchar();
        s = 0;
        while (!isdigit(ch) && ch != EOF && ch != '.')
            f = (ch == '-' ? -1 : 1), ch = getchar();
        while (isdigit(ch))
            s = s * 10 + (ch ^ 48), ch = getchar();
        if (ch == EOF)
            return false;
        if (ch == '.')
        {
            Tp eps = 0.1;
            ch = getchar();
            while (isdigit(ch))
                s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10;
        }
        s *= f;
        return ch != EOF;
    }
    inline int read(char &c) {
        char ch = getchar();
        c = EOF;
        while (isspace(ch) && ch != EOF)
            ch = getchar();
        if (ch != EOF)
            c = ch;
        return c != EOF;
    }
    inline int read(char *c) {
        char ch = getchar(), *s = c;
        while (isspace(ch) && ch != EOF)
            ch = getchar();
        while (!isspace(ch) && ch != EOF)
            *(c++) = ch, ch = getchar();
        *c = '\0';
        return s != c;
    }
    inline int read(string &s) {
        s.clear();
        char ch = getchar();
        while (isspace(ch) && ch != EOF)
            ch = getchar();
        while (!isspace(ch) && ch != EOF)
            s += ch, ch = getchar();
        return s.size() > 0;
    }
    inline int getline(char *c, const char &ed = '\n') {
        char ch = getchar(), *s = c;
        while (ch != ed && ch != EOF)
            *(c++) = ch, ch = getchar();
        *c = '\0';
        return s != c;
    }
    inline int getline(string &s, const char &ed = '\n') {
        s.clear();
        char ch = getchar();
        while (ch != ed && ch != EOF)
            s += ch, ch = getchar();
        return s.size() > 0;
    }
    template <typename Tp = int>
    inline Tp read() {
        Tp x;
        read(x);
        return x;
    }
    template <typename Tp, typename... Ts>
    int read(Tp &x, Ts &...val) { return read(x) && read(val...); }
    template <typename Tp, typename enable_if<is_integral<Tp>::value>::type * = nullptr>
    IO &write(Tp x) {
        if (x < 0) putchar('-'), x = -x;
        static char sta[20];
        int top = 0;
        do sta[top++] = x % 10 + '0', x /= 10;
        while (x);
        while (top) putchar(sta[--top]);
        return *this;
    }
    inline IO &write(const string &str) {
        for (char ch : str) putchar(ch);
        return *this;
    }
    inline IO &write(const char *str) {
        while (*str != '\0') putchar(*(str++));
        return *this;
    }
    inline IO &write(char *str) { return write((const char *)str); }
    inline IO &write(const char &ch) { return putchar(ch), *this; }
    template <typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>
    inline IO &write(Tp x) {
        if (x > 1e18 || x < -1e18) {
            write("[Floating point overflow]");
            throw;
        }
        if (x < 0)
            putchar('-'), x = -x;
        const static long long pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 100000000000000000, 100000000000000000};
        const auto &n = pow10[k];
        long long whole = (int)x;
        double tmp = (x - whole) * n;
        long long frac = tmp;
        double diff = tmp - frac;
        if (diff > 0.5) {
            ++frac;
            if (frac >= n) frac = 0, ++whole;
        }
        else if (diff == 0.5 && ((frac == 0U) || (frac & 1U)))
            ++frac;
        write(whole);
        if (k == 0U) {
            diff = x - (double)whole;
            if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1)) ++whole;
        } else {
            putchar('.');
            static char sta[20];
            int count = k, top = 0;
            while (frac) {
                sta[top++] = frac % 10 + '0';
                frac /= 10, count--;
            }
            while (count--) putchar('0');
            while (top) putchar(sta[--top]);
        }
        return *this;
    }
    template <typename Tp, typename... Ts>
    inline IO &write(Tp x, Ts... val) {
        write(x);
        write(sep);
        write(val...);
        return *this;
    }
    template <typename... Ts>
    inline IO &writeln(Ts... val) {
        write(val...);
        putchar('\n');
        return *this;
    }
    inline IO &writeln(void) {
        putchar('\n');
        return *this;
    }
    template <typename Tp>
    inline IO &writeWith(Tp x, const string &s = " ") {
        write(x), write(s);
        return *this;
    }
    inline IO &setsep(const string &s) { return sep = s, *this; }
    inline IO &setprec(const int &K) { return k = K, *this; }
} io;

// Warning: this uses nearly 170 MB for N = 500,000. If low on memory use memory_rmq_lca.cc or block_rmq_lca.cc instead
template<typename T, bool maximum_mode = false>
struct RMQ {
    static int highest_bit(unsigned x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }

    int n = 0;
    vector<T> values;
    vector<vector<int>> range_low;

    RMQ(const vector<T> &_values = {}) {
        if (!_values.empty())
            build(_values);
    }

    // Note: when `values[a] == values[b]`, returns b.
    int better_index(int a, int b) const {
        return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
    }

    void build(const vector<T> &_values) {
        values = _values;
        n = int(values.size());
        int levels = highest_bit(n) + 1;
        range_low.resize(levels);

        for (int k = 0; k < levels; k++)
            range_low[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_low[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
    }

    // Note: breaks ties by choosing the largest index.
    int query_index(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int level = highest_bit(b - a);
        return better_index(range_low[level][a], range_low[level][b - (1 << level)]);
    }

    T query_value(int a, int b) const {
        return values[query_index(a, b)];
    }
};

struct LCA {
    int n = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree_size;
    vector<int> euler, first_occurrence;
    vector<int> tour_start, tour_end;
    vector<int> tour_list, rev_tour_list;
    vector<int> heavy_root;
    vector<int> heavy_root_depth, heavy_root_parent;  // These two vectors serve purely to optimize get_kth_ancestor
    RMQ<int> rmq;
    bool built = false;

    LCA(int _n = 0) {
        init(_n);
    }

    // Warning: this does not call build().
    LCA(const vector<vector<int>> &_adj) {
        init(_adj);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        subtree_size.resize(n);
        first_occurrence.resize(n);
        tour_start.resize(n);
        tour_end.resize(n);
        tour_list.resize(n);
        heavy_root.resize(n);
        built = false;
    }

    // Warning: this does not call build().
    void init(const vector<vector<int>> &_adj) {
        init(int(_adj.size()));
        adj = _adj;
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int degree(int v) const {
        return int(adj[v].size()) + (built && parent[v] >= 0);
    }

    void dfs(int node, int par) {
        parent[node] = par;
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        subtree_size[node] = 1;

        // Erase the edge to parent.
        adj[node].erase(remove(adj[node].begin(), adj[node].end(), par), adj[node].end());

        for (int child : adj[node]) {
            dfs(child, node);
            subtree_size[node] += subtree_size[child];
        }

        // Heavy-light subtree reordering.
        sort(adj[node].begin(), adj[node].end(), [&](int a, int b) {
            return subtree_size[a] > subtree_size[b];
        });
    }

    int tour;

    void tour_dfs(int node, bool heavy) {
        heavy_root[node] = heavy ? heavy_root[parent[node]] : node;
        first_occurrence[node] = int(euler.size());
        euler.push_back(node);
        tour_list[tour] = node;
        tour_start[node] = tour++;
        bool heavy_child = true;

        for (int child : adj[node]) {
            tour_dfs(child, heavy_child);
            euler.push_back(node);
            heavy_child = false;
        }

        tour_end[node] = tour;
    }

    void build(vector<int> roots = {}, bool build_rmq = true) {
        depth.assign(n, -1);

        for (int root : roots)
            if (depth[root] < 0)
                dfs(root, -1);

        for (int i = 0; i < n; i++)
            if (depth[i] < 0)
                dfs(i, -1);

        tour = 0;
        euler.clear();
        euler.reserve(2 * n);

        for (int i = 0; i < n; i++)
            if (parent[i] < 0) {
                tour_dfs(i, false);
                // Add a -1 in between connected components to help us detect when nodes aren't connected.
                euler.push_back(-1);
            }

        assert(int(euler.size()) == 2 * n);
        vector<int> euler_depth;
        euler_depth.reserve(euler.size());

        for (int node : euler)
            euler_depth.push_back(node < 0 ? node : depth[node]);

        if (build_rmq)
            rmq.build(euler_depth);

        euler_depth.clear();
        heavy_root_depth.resize(n);
        heavy_root_parent.resize(n);

        for (int i = 0; i < n; i++) {
            heavy_root_depth[i] = depth[heavy_root[i]];
            heavy_root_parent[i] = parent[heavy_root[i]];
        }

        rev_tour_list = tour_list;
        reverse(rev_tour_list.begin(), rev_tour_list.end());
        built = true;
    }

    pair<int, array<int, 2>> get_diameter() const {
        assert(built);

        // We find the maximum of depth[u] - 2 * depth[x] + depth[v] where u, x, v occur in order in the Euler tour.
        pair<int, int> u_max = {-1, -1};
        pair<int, int> ux_max = {-1, -1};
        pair<int, array<int, 2>> uxv_max = {-1, {-1, -1}};

        for (int node : euler) {
            if (node < 0) break;
            u_max = max(u_max, {depth[node], node});
            ux_max = max(ux_max, {u_max.first - 2 * depth[node], u_max.second});
            uxv_max = max(uxv_max, {ux_max.first + depth[node], {ux_max.second, node}});
        }

        return uxv_max;
    }

    // Returns the center(s) of the tree (the midpoint(s) of the diameter).
    array<int, 2> get_center() const {
        pair<int, array<int, 2>> diam = get_diameter();
        int length = diam.first, a = diam.second[0], b = diam.second[1];
        return {get_kth_node_on_path(a, b, length / 2), get_kth_node_on_path(a, b, (length + 1) / 2)};
    }

    // Note: returns -1 if `a` and `b` aren't connected.
    int get_lca(int a, int b) const {
        a = first_occurrence[a];
        b = first_occurrence[b];

        if (a > b)
            swap(a, b);

        return euler[rmq.query_index(a, b + 1)];
    }

    bool is_ancestor(int a, int b) const {
        return tour_start[a] <= tour_start[b] && tour_start[b] < tour_end[a];
    }

    bool on_path(int x, int a, int b) const {
        return (is_ancestor(x, a) || is_ancestor(x, b)) && is_ancestor(get_lca(a, b), x);
    }

    int get_dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }

    // Returns the child of `a` that is an ancestor of `b`. Assumes `a` is a strict ancestor of `b`.
    int child_ancestor(int a, int b) const {
        assert(a != b && is_ancestor(a, b));

        // Note: this depends on RMQ breaking ties by latest index.
        int child = euler[rmq.query_index(first_occurrence[a], first_occurrence[b] + 1) + 1];
        // assert(parent[child] == a && is_ancestor(child, b));
        return child;
    }

    int get_kth_ancestor(int a, int k) const {
        if (k > depth[a])
            return -1;

        int goal = depth[a] - k;

        while (heavy_root_depth[a] > goal)
            a = heavy_root_parent[a];

        return tour_list[tour_start[a] + goal - depth[a]];
    }

    int get_kth_node_on_path(int a, int b, int k) const {
        int anc = get_lca(a, b);
        int first_half = depth[a] - depth[anc];
        int second_half = depth[b] - depth[anc];

        if (k < 0 || k > first_half + second_half)
            return -1;

        if (k < first_half)
            return get_kth_ancestor(a, k);
        else
            return get_kth_ancestor(b, first_half + second_half - k);
    }

    // Note: this is the LCA of any two nodes out of three when the third node is the root.
    // It is also the node with the minimum sum of distances to all three nodes (the centroid of the three nodes).
    int get_common_node(int a, int b, int c) const {
        // Return the deepest node among lca(a, b), lca(b, c), and lca(c, a).
        int x = get_lca(a, b);
        int y = get_lca(b, c);
        int z = get_lca(c, a);
        return x ^ y ^ z;
    }

    // Given a subset of k tree nodes, computes the minimal subtree that contains all the nodes (at most 2k - 1 nodes).
    // Returns a list of {node, parent} for every node in the subtree sorted by tour index. Runs in O(k log k).
    // Note that all parents also appear as a node in the return value, and nodes[0].first is the compressed root.
    vector<pair<int, int>> compress_tree(vector<int> nodes) const {
        if (nodes.empty())
            return {};

        auto compare_tour = [&](int a, int b) -> bool { return tour_start[a] < tour_start[b]; };
        sort(nodes.begin(), nodes.end(), compare_tour);
        int k = int(nodes.size());

        for (int i = 0; i < k - 1; i++)
            nodes.push_back(get_lca(nodes[i], nodes[i + 1]));

        sort(nodes.begin() + k, nodes.end(), compare_tour);
        inplace_merge(nodes.begin(), nodes.begin() + k, nodes.end(), compare_tour);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> result = {{nodes[0], -1}};

        for (int i = 1; i < int(nodes.size()); i++)
            result.emplace_back(nodes[i], get_lca(nodes[i], nodes[i - 1]));

        return result;
    }
};

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

// wavelet_matrix takes an array v and preprocesses the data in O(n log n) to answer the following queries in O(log n):
// 1) count v[i] = x for i in [start, end)
// 2) count v[i] < upper for i in [start, end)
// 3) find the k-th smallest / k-th largest v[i] for i in [start, end), k in [0, m), m: number of distinct v[i] for i in [start, end)
// 4) find the smallest value >= lower / largest value < upper for i in [start, end)
template<typename T>
struct wavelet_matrix {
    int n, levels;
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