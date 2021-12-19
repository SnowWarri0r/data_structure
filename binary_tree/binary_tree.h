//
// Created by SnowWarrior on 2021/12/9.
//

#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

#include<iostream>
#include<queue>
#include<stack>
#include <utility>
#include <vector>

using std::queue;
using std::cout;
using std::stack;
using std::pair;
using std::vector;

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

    BinarySearchTree(vector<int> &pre, vector<int> &mid) {
        root = buildTree(0, 0, mid.size() - 1, pre, mid);
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
            while (p != nullptr) {
                cout << p->data << " ";
                stack.push(p);
                p = p->left;
            }
            if (!stack.empty()) {
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
            while (p != nullptr) {
                stack.push(p);
                p = p->left;
            }
            p = stack.top();
            if (p->right == nullptr || pre == p->right) {
                cout << p->data << " ";
                pre = p;
                stack.pop();
                p = nullptr;
            } else {
                p = p->right;
            }
        }
    }

    bool equal(BinarySearchTree &tree) {
        TreeNode<int> *p1 = root, *p2 = tree.root;
        return isSameTree(p1, p2);
    }

    void swapChildren() {
        TreeNode<int> *p = root;
        swap(p);
    }

    //返回先序遍历最后一个节点地址和后序遍历第一个节点地址
    pair<TreeNode<int> *, TreeNode<int> *> firstAndLast() const {
        pair<TreeNode<int> *, TreeNode<int> *> pair;
        TreeNode<int> *p1 = root, *p2 = root;
        while (p1 != nullptr) {
            if (p1->right != nullptr) {
                p1 = p1->right;
            } else if (p1->left != nullptr) {
                p1 = p1->left;
            } else break;
        }
        pair.first = p1;
        while (p2 != nullptr) {
            if (p2->left != nullptr) {
                p2 = p2->left;
            } else if (p2->right != nullptr) {
                p2 = p2->right;
            } else break;
        }
        pair.second = p2;
        return pair;
    }

    int depth(int x) const {
        TreeNode<int> *p = root;
        queue<TreeNode<int> *> q;
        q.push(p);
        int sum = 0;
        while (!q.empty()) {
            p = q.front();
            q.pop();
            sum++;
            if (p->data == x) {
                while (!q.empty()) q.pop();
                break;
            }
            if (p->left != nullptr) q.push(p->left);
            if (p->right != nullptr) q.push(p->right);
        }
        sum++;
        int ans = 0;
        while (sum != 0) {
            sum >>= 1;
            ans++;
        }
        return ans;
    }


private:
    /**
     * 根据先序遍历序列和中序遍历序列构造二叉树
     * @param preStart 当前根节点在pre中的下标
     * @param inStart 以pre[preStart]为根节点的子树的节点值在mid中的范围起点
     * @param inEnd 以pre[preStart]为根节点的子树的节点值在mid中的范围终点
     * @param pre 先序遍历序列
     * @param mid 中序遍历序列
     * @return 构造出的二叉树
     */
    TreeNode<int> *buildTree(int preStart, int inStart, int inEnd, vector<int> &pre, vector<int> &mid) {
        if (preStart >= pre.size() || inStart > inEnd) return nullptr;

        auto *subRoot = new TreeNode<int>(pre[preStart]);
        int inIndex = 0;
        for (int i = inStart; i <= inEnd; i++) {
            if (mid[i] == pre[preStart]) {
                inIndex = i;
                break;
            }
        }
        subRoot->left = buildTree(preStart + 1, inStart, inIndex - 1, pre, mid);
        subRoot->right = buildTree(preStart + 1 + inIndex - inStart, inIndex + 1, inEnd, pre, mid);
        return subRoot;
    }

    void swap(TreeNode<int> *node) {
        if (node->left != nullptr) swap(node->left);
        if (node->right != nullptr) swap(node->right);
        TreeNode<int> *temp = node->left;
        node->left = node->right;
        node->right = temp;
    }

    bool isSameTree(TreeNode<int> *p1, TreeNode<int> *p2) {
        if (p1 == nullptr && p2 == nullptr) return true;
        if (p1 == nullptr || p2 == nullptr) return false;
        if (p1->data != p2->data) return false;
        return isSameTree(p1->left, p2->left) && isSameTree(p1->right, p2->right);
    }

private:
    TreeNode<int> *root;
};

#endif //BINARY_TREE_BINARY_TREE_H
