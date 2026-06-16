#include <iostream>
#include <string>
using namespace std;

// 根据前序和中序序列递归构建二叉树，返回后序序列
string buildPostOrder(const string& pre, int preBeg, int preEnd,
                      const string& in,  int inBeg,  int inEnd) {
    if (preBeg > preEnd || inBeg > inEnd) {
        return "";
    }

    // 前序的第一个字符就是当前子树的根
    char root = pre[preBeg];

    // 在中序中找到根的位置
    int rootPos = inBeg;
    while (rootPos <= inEnd && in[rootPos] != root) {
        ++rootPos;
    }

    int leftSize = rootPos - inBeg;   // 左子树结点数
    int rightSize = inEnd - rootPos;  // 右子树结点数

    // 递归得到左子树的后序
    string leftPost = buildPostOrder(pre, preBeg + 1,              preBeg + leftSize,
                                     in,  inBeg,                   rootPos - 1);

    // 递归得到右子树的后序
    string rightPost = buildPostOrder(pre, preBeg + leftSize + 1,  preEnd,
                                      in,  rootPos + 1,            inEnd);

    // 后序：左 + 右 + 根
    return leftPost + rightPost + root;
}

int main() {
    string preOrder, inOrder;
    // 输入前序序列和中序序列（无空格，例如：ABDEC DBACE）
    cin >> preOrder >> inOrder;

    int n = static_cast<int>(preOrder.size());
    string postOrder = buildPostOrder(preOrder, 0, n - 1, inOrder, 0, n - 1);

    cout << postOrder << endl;
    return 0;
}
