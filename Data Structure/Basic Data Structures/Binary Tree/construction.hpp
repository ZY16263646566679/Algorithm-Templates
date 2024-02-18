// 分治法构造二叉树
#include <bits/stdc++.h>
using namespace std;

/**
 * 已知前序中序遍历求后序遍历
 * 需保证字符串中的字符不重复
 * 可用哈希表优化
 */
void post(string pre, string in) {
    if (pre.empty()) return;
    int k = in.find(pre[0]);
    pre.erase(pre.begin());
    post(pre.substr(0, k), in.substr(0, k));
    post(pre.substr(k), in.substr(k + 1));
    cout << pre[0];
}

/**
 * 对于已知后序中序遍历求前序遍历同理
 * 后序遍历的倒序就是“右前序”遍历（根->右儿子->左儿子）
 * 前序遍历的倒序就是“右后序”遍历（右儿子->左儿子->根）
 * 
 * 对于已知前序遍历和后序遍历，树的形状不唯一
 * 原因是，若某个节点只有一个儿子时，无法判断该儿子是左儿子还是右儿子
 * 其它情况可以保证唯一
 */