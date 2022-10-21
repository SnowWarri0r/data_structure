#include "binary_tree.h"

using std::cin;

void test();

void test1();

void test2();

void test3();

void test4();

int main() {
//    BinarySearchTree tree;
//    int n;
//    cout << "请输入需要插入二叉树的元素个数：";
//    cin >> n;
//    int data;
//    for (int i = 0; i < n; ++i) {
//        cin >> data;
//        tree.insert(data);
//    }
//    tree.bfs();
//    cout<<std::endl;
//    tree.preOrderTraversal();
//    cout<<std::endl;
//    tree.postOrderTraversal();
//    cout<<std::endl;
//    test();
    test1();
    test2();
    test3();
    test4();
    return 0;
}

void test() {
    BinarySearchTree tree1, tree2;
    int n;
    cout << "请输入需要插入二叉树的元素个数：";
    cin >> n;
    int data;
    for (int i = 0; i < n; ++i) {
        cin >> data;
        tree1.insert(data);
    }
    cout << "请输入需要插入二叉树的元素个数：";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> data;
        tree2.insert(data);
    }
    cout << tree1.equal(tree2);
}

void test1() {
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
    tree.swapChildren();
    cout << "\nswap children\n";
    tree.bfs();
    tree.swapChildren();
    cout << "\nswap children\n";
    tree.bfs();
}

void test2() {
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
    auto[a, b]=tree.firstAndLast();
    cout << a->data << " " << b->data << std::endl;
}

void test3() {
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
    cout << "请输入x：";
    int x;
    cin >> x;
    cout << tree.depth(x);
}

void test4() {
    vector<int> pre, mid;
    cout << "请输入序列长度：";
    int n;
    cin >> n;
    cout << "请输入先序遍历序列：";
    int data;
    for (int i = 0; i < n; ++i) {
        cin >> data;
        pre.push_back(data);
    }
    cout << "请输入中序遍历序列：";
    for (int i = 0; i < n; ++i) {
        cin >> data;
        mid.push_back(data);
    }
    BinarySearchTree tree(pre, mid);
    tree.bfs();
}