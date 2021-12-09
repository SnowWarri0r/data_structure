//
// Created by SnowWarrior on 2021/12/9.
//

#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

#include<iostream>
#include<queue>
#include<stack>

using std::queue;
using std::cout;
using std::stack;

template<typename T>
struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : left(nullptr), right(nullptr) {}

    explicit TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}
};

//template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree() {
        root = nullptr;
    }

    bool insert(int data) {
        if (root == nullptr) {
            root = new TreeNode<int>(data);
            return true;
        }
        TreeNode<int> *parent, *p = root;
        while (p != nullptr) {
            if (p->data == data) {
                return false;
            }
            if (p->data < data) {
                parent = p;
                p = p->right;
            } else if (p->data > data) {
                parent = p;
                p = p->left;
            }
        }
        if (data > parent->data) {
            parent->right = new TreeNode<int>(data);
        } else if (data < parent->data) {
            parent->left = new TreeNode<int>(data);
        }
        return true;
    }

    bool remove(int data) {
        TreeNode<int> *parent, *p = root;
        while (p != nullptr) {
            if (p->data == data) {
                //删除的节点只有左孩子或没有孩子节点
                if (p->right == nullptr) {
                    if (p == root) {
                        root = root->left;
                    } else if (parent->left == p) {
                        parent->left = p->left;
                    } else {
                        parent->right = p->left;
                    }
                    delete p;
                    return true;
                } else if (p->left == nullptr) {
                    //删除的节点只有右孩子或没有孩子节点
                    if (p == root) {
                        root = root->right;
                    } else if (parent->left == p) {
                        parent->left = p->right;
                    } else {
                        parent->right = p->right;
                    }
                    delete p;
                    return true;
                } else {
                    //删除的节点有左右孩子
                    parent = p;
                    TreeNode<int> *child = p->right;
                    while (child->left != nullptr) {
                        parent = child;
                        child = child->left;
                    }
                    p->data = child->data;
                    if (parent->right == child) {
                        parent->right = child->right;
                    } else {
                        parent->left = child->right;
                    }
                    delete child;
                    return true;
                }
            }
            if (p->data < data) {
                parent = p;
                p = p->right;
            } else if (p->data < data) {
                parent = p;
                p = p->left;
            }
        }
        return false;
    }

    void bfs() {
        queue<TreeNode<int> *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode<int> *node = q.front();
            q.pop();
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
            cout << node->data << " ";
        }
    }

    void preOrderTraversal() {
        stack<TreeNode<int> *> stack;
        TreeNode<int> *p = root;
        while (p != nullptr || !stack.empty()) {
            if (p != nullptr) {
                cout << p->data << " ";
                stack.push(p);
                p = p->left;
            } else {
                p = stack.top();
                stack.pop();
                p = p->right;
            }
        }
    }

    void postOrderTraversal() {
        stack<TreeNode<int> *> stack;
        TreeNode<int> *p = root, *pre = nullptr;
        while (p != nullptr || !stack.empty()) {
            if (p != nullptr) {
                stack.push(p);
                p = p->left;
            } else {
                p = stack.top();
                stack.pop();
                if (p->right == nullptr || pre == p->right) {
                    cout << p->data << " ";
                    pre = p;
                    p = nullptr;
                } else {
                    stack.push(p);
                    p = p->right;
                }
            }
        }
    }

private:
    TreeNode<int> *root;
};

#endif //BINARY_TREE_BINARY_TREE_H
