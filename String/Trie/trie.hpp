// 字典树
#include <bits/stdc++.h>
using namespace std;

class Trie {
private:
    vector<Trie*> children;
    bool isEnd;

    Trie* searchPrefix(string prefix) {
        Trie* node = this;
        for (char ch : prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }
public:
    Trie() : children(26), isEnd(false) {}

    void insert(string word) {
        Trie* node = this;
        for (char ch : word) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        return this->searchPrefix(prefix) != nullptr;
    }
};

// 静态数组存储
const int N = 1e6 + 5;
int trie[N][26], id; // 0为根节点，trie[i][j]表示id为i的节点的子节点j的id
int num[N], v[N]; // num[i]：这个前缀出现的次数，v[i]：这个单词对应的值

void insert(string& s, int val) {
    int p = 0;
    for(int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[p][c]) trie[p][c] = ++id;
        p = trie[p][c];
        num[p]++; // 出现次数加一
    }
    v[p] = val; // 存储值
}

int search_prefix(string& s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        p = trie[p][s[i] - 'a'];
        if (!p) return 0; // 找不到
    }
    return num[p]; // 返回这个前缀的出现次数
}