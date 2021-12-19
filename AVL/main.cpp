#include "avl.h"

using std::cin;

int main() {
    AVL tree;
    cout << "请输入需要插入二叉树的元素个数：";
    int n;
    cin >> n;
    int data;
    for (int i = 0; i < n; ++i) {
        cin >> data;
        tree.insert(data);
    }
    tree.level_order_traversal();
    tree.pre_order_traversal();
    tree.in_order_traversal();
    tree.post_order_traversal();
    return 0;
}
