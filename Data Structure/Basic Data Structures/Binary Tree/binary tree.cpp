// 二叉树
#include <bits/stdc++.h>
using namespace std;

// 动态二叉树：优点是不浪费空间，缺点是需要管理
struct Node {
    int val;
    Node* l, * r;
    Node(int val = 0, Node* l = nullptr, Node* r = nullptr) : val(val), l(l), r(r) {}
};

// 先序遍历
void preorder(Node* root, vector<int>& post) {
    if (root) {
        post.push_back(root->val);
        preorder(root->l, post);
        preorder(root->r, post);
    }
}
// 中序遍历
void inorder(Node* root, vector<int>& post) {
    if (root) {
        inorder(root->l, post);
        post.push_back(root->val);
        inorder(root->r, post);
    }
}
// 后序遍历
void postorder(Node* root, vector<int>& post) {
    if (root) {
        postorder(root->l, post);
        postorder(root->r, post);
        post.push_back(root->val);
    }
}

// 静态二叉树：编码简单，速度快
const int N = 1e5 + 5;
int n;
struct {
    int val;
    int l, r;
} t[N]; // 节点下标从1开始

/* 或者直接用三个数组来存储 */
int l[N], r[N], val[N];