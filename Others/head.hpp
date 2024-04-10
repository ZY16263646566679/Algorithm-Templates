#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
// #define int long long // 全局替换
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<double, double>;
using pld = pair<ld, ld>;
using vi = vector<int>;
using vll = vector<ll>;
using vd = vector<double>;
using vld = vector<ld>;
using vpii = vector<pii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvd = vector<vd>;
using vvld = vector<vld>;
#define mp make_pair
using lll = __int128_t;
using __gnu_cxx::crope;
using __gnu_cxx::rope; // rope<char>可用crope代替
template<class V = null_type>
using Trie = trie<string, V, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update>;
template<class K, class V = null_type, class Cmp = less<>>
using rb = tree<K, V, Cmp, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V = null_type, class Cmp = less<>>
using splay = tree<K, V, Cmp, splay_tree_tag, tree_order_statistics_node_update>;
template<class K, class V = null_type, class Cmp = less<>>
using ov = tree<K, V, Cmp, ov_tree_tag, tree_order_statistics_node_update>;
using __gnu_pbds::cc_hash_table, __gnu_pbds::gp_hash_table; // faster read/write or insertion
template<class T, class Cmp = less<T>> using heap = __gnu_pbds::priority_queue<T, Cmp, pairing_heap_tag>;
#define priority_queue std::priority_queue
#define err(color) cout << "\033[" << color << "m"
enum { red = 31, green, yellow, blue, purple, cyan }; // 31红，32绿，33黄，34蓝，35紫，36青
#define cl "\033[0m" << endl
#define yn(ans) printf("%s\n", (ans) ? "Yes" : "No")
#define YN(ans) printf("%s\n", (ans) ? "YES" : "NO")
#define rep(i, s, e, t) for (int i = s; i < e; i += t)
#define For(i, n) for (int i = 1; i <= n; i++)
#define FOR(i, e, n) for (int i = e; i <= n; i++)
template<class T> bool chmax(T& a, T b) {
    if (a >= b) return false;
    a = b; return true;
}
template<class T> bool chmin(T& a, T b) {
    if (a <= b) return false;
    a = b; return true;
}
#define endl '\n'
#define ln(x) log(x)
#define lg(x) log10(x)
#define all(v) v.begin(), v.end()
#define pb push_back
#define qb pop_back
#define pf push_front
#define qf pop_front
#define maxe max_element
#define mine min_element
const long double e = 2.7182818284590452354l; // 可以精确到第18位小数
#define DEBUG printf("%d\n", __LINE__); fflush(stdout);

template<class T> void print(vector<T>& v, bool withSize) {
    if (withSize) cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

ostream& operator<<(ostream& stream, __int128_t x) { // 最大3.4*10^38
    if (x < 0) stream << '-', x = -x;
    if (x / 10) operator<<(stream, x / 10);
    stream << char(x % 10 + '0');
    return stream;
}

string format(string& s) { return s; }
template<typename T> string format(const T& x) { return to_string(x); }
template<typename K, typename V>
string format(const pair<K, V>& x) { return format(x.first) + "," + format(x.second); }

#define print(x) \
	for (int c = rand() % 6 + 31; auto& i : x) \
		err(c) << format(i) << ' '; \
	cout << cl; \

template<typename A, typename B>
ostream& operator<<(ostream &os, const pair<A, B> &p) {
	return os << '(' << p.first << ", " << p.second << ')';
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream& operator<<(ostream &os, const T_container &v) {
	os << '{';
	string sep;
	for (const T &x : v)
		os << sep << x, sep = ", ";
	return os << '}';
}

inline void read(auto& t, auto&... args) {
    char sign = 1, c = getchar(); t = 0;
    while (c < '0' || '9' < c) { if (c == '-') sign = -1; c = getchar(); }
    while ('0' <= c && c <= '9') t = t * 10 + c - '0', c = getchar();
    t *= sign;
    if constexpr (sizeof...(args)) read(args...);
}

static const auto FAST_IO = [] {
    cin.tie(0) -> sync_with_stdio(0);
    return nullptr;
};

// 打印运行时间
void print_time(void fun() = nullptr) {
    clock_t begin, end;
    begin = clock();
    // fun(); //计算fun函数的运行时间
    end = clock();
    printf("%3.3f\n", 1.0 * (end - begin) / CLOCKS_PER_SEC);
}