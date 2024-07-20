#include <bits/extc++.h>
using namespace std;

// 字符串分割
vector<string> split(const string& s, char limit = ' ') {
    vector<string> res;
    int i = -1, j = 0, len = s.length();
    while (j < len) {
        j = i + 1;
        while (j < len && s[j] != limit) j++;
        if (j > i + 1) res.push_back(string(s.begin() + i + 1, s.begin() + j));
        i = j;
    }
    return res;
}

// 正则表达式匹配
void regexSearch() {
    string s = "abad";
    regex r("a\\w");
    smatch m;
    while (regex_search(s, m, r)) {
        cout << m[0] << endl;
        s = m.suffix().str();
    }
}