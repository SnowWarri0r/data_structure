#include "binary_tree.h"

using std::cin;

int main() {
    BinarySearchTree tree;
    int n;
    cout << "请输入需要插入二叉树的元素个数：";
    cin >> n;
    int data;
    for (int i = 0; i < n; ++i) {
        cin >> data;
        tree.insert(data);
    }
    tree.bfs();
    tree.preOrderTraversal();

    return 0;
}
