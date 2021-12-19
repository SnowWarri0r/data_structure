//
// Created by SnowWarrior on 2021/12/19.
//

#ifndef AVL_AVL_H
#define AVL_AVL_H

#include <queue>
#include <stack>
#include <iostream>
#include <cmath>

using std::max;
using std::cout;
using std::endl;
using std::queue;
using std::stack;

struct TreeNode {
    int val;
    int height{};
    TreeNode *left{};
    TreeNode *right{};

    explicit TreeNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), height(1), left(left), right(right) {}
};

class AVL {
public:
    AVL() {
        root = nullptr;
    }

    ~AVL() {
        clear();
    }

    int height() const {
        return tree_height(root);
    }

    void insert(int x) {
        root = tree_insert_node(root, x);
    }

    void erase(int x) {
        TreeNode *z;
        if ((z = tree_search(root, x)) != nullptr) {
            root = tree_delete_node(root, z);
        }
    }

    void pre_order_traversal() {
        iterative_pre_order_traversal(root);
    }

    void in_order_traversal() {
        iterative_inorder_traversal(root);
    }

    void post_order_traversal() {
        iterative_post_order_traversal(root);
    }

    TreeNode *search(int x) {
        return iterative_tree_search(root, x);
    }

    void clear() {
        destroy_tree(root);
    }

private:
    static int tree_height(TreeNode *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    /**
     * （递归实现）查找AVL树中是否存在键值为x的节点
     * @param tree 树根节点
     * @param x 查找的值
     * @return 查找到的节点
     */
    TreeNode *tree_search(TreeNode *tree, int x) {
        if (tree == nullptr) {
            return nullptr;
        }
        if (tree->val == x) {
            return tree;
        }
        if (tree->val > x) {
            return tree_search(tree->left, x);
        } else {
            return tree_search(tree->right, x);
        }
    }

    /**
     * （非递归实现）查找AVL树中是否存在键值为x的节点
     * @param tree 树根节点
     * @param x 查找的值
     * @return 查找到的节点
     */
    static TreeNode *iterative_tree_search(TreeNode *tree, int x) {
        while (tree != nullptr) {
            if (tree->val == x) {
                return tree;
            }
            if (tree->val > x) {
                tree = tree->left;
            } else {
                tree = tree->right;
            }
        }
        return nullptr;
    }

    static void tree_pre_order_traversal(TreeNode *tree) {
        if (tree == nullptr) {
            return;
        }
        cout << tree->val << " ";
        tree_pre_order_traversal(tree->left);
        tree_pre_order_traversal(tree->right);
    }

    static void iterative_pre_order_traversal(TreeNode *tree) {
        if (tree == nullptr) {
            return;
        }
        stack<TreeNode *> stack;
        stack.push(tree);
        TreeNode *node = tree;
        while (node != nullptr || !stack.empty()) {
            if (node != nullptr) {
                cout << node->val << " ";
                stack.push(node);
                node = node->left;
            } else {
                node = stack.top();
                stack.pop();
                node = node->right;
            }
        }
    }

    static void tree_inorder_traversal(TreeNode *tree) {
        if (tree == nullptr) {
            return;
        }
        tree_inorder_traversal(tree->left);
        cout << tree->val << " ";
        tree_inorder_traversal(tree->right);
    }

    static void iterative_inorder_traversal(TreeNode *tree) {
        if (tree == nullptr) {
            return;
        }
        stack<TreeNode *> stack;
        TreeNode *node = tree;
        while (node != nullptr || !stack.empty()) {
            while (node != nullptr) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            cout << node->val << " ";
            node = node->right;
        }
    }

    static void tree_post_order_traversal(TreeNode *tree) {
        if (tree == nullptr) {
            return;
        }
        tree_post_order_traversal(tree->left);
        tree_post_order_traversal(tree->right);
        cout << tree->val << " ";
    }

    static void iterative_post_order_traversal(TreeNode *tree) {
        if (tree == nullptr) {
            return;
        }
        stack<TreeNode *> stack;
        TreeNode *node = tree;
        TreeNode *prev = nullptr;
        while (node != nullptr || !stack.empty()) {
            while (node != nullptr) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            if (node->right == nullptr || node->right == prev) {
                cout << node->val << " ";
                prev = node;
                stack.pop();
                node = nullptr;
            } else {
                node = node->right;
            }
        }
    }

    static TreeNode *tree_maximum(TreeNode *tree) {
        if (tree == nullptr) {
            return nullptr;
        }
        while (tree->right != nullptr) {
            tree = tree->right;
        }
        return tree;
    }

    static TreeNode *tree_minimum(TreeNode *tree) {
        if (tree == nullptr) {
            return nullptr;
        }
        while (tree->left != nullptr) {
            tree = tree->left;
        }
        return tree;
    }

    /**
     * LL:左左对应的情况（左单旋转）
     * @return 旋转后的根节点
     */
    static TreeNode *left_left_rotation(TreeNode *node) {
        TreeNode *new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        node->height = max(tree_height(node->left), tree_height(node->right)) + 1;
        new_root->height = max(tree_height(new_root->left), node->height) + 1;
        return new_root;
    }

    /**
     * RR:右右对应的情况（右单旋转）
     * @return 旋转后的根节点
     */
    static TreeNode *right_right_rotation(TreeNode *node) {
        TreeNode *new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        node->height = max(tree_height(node->left), tree_height(node->right)) + 1;
        new_root->height = max(tree_height(new_root->right), node->height) + 1;
        return new_root;
    }

    /**
     * LR:左右对应的情况（左双旋转）
     * @return 旋转后的根节点
     */
    static TreeNode *left_right_rotation(TreeNode *node) {
        node->left = right_right_rotation(node->left);
        return left_left_rotation(node);
    }

    /**
     * RL:右左对应的情况（右双旋转）
     * @return 旋转后的根节点
     */
    static TreeNode *right_left_rotation(TreeNode *node) {
        node->right = left_left_rotation(node->right);
        return right_right_rotation(node);
    }

    TreeNode *tree_insert_node(TreeNode *tree, int x) {
        if (tree == nullptr) {
            return new TreeNode(x);
        }
        if (x < tree->val) {
            //将节点插入到左子树的情况
            tree->left = tree_insert_node(tree->left, x);
            //插入节点后，若AVL树失去平衡，则进行相应的调整
            if (tree_height(tree->left) - tree_height(tree->right) == 2) {
                if (x < tree->left->val) {
                    tree = left_left_rotation(tree);
                } else {
                    tree = left_right_rotation(tree);
                }
            }
        } else if (x > tree->val) {
            //应该将节点插入到右子树的情况
            tree->right = tree_insert_node(tree->right, x);
            //插入节点后，若AVL树失去平衡，则进行相应的调整
            if (tree_height(tree->right) - tree_height(tree->left) == 2) {
                if (x > tree->right->val) {
                    tree = right_right_rotation(tree);
                } else {
                    tree = right_left_rotation(tree);
                }
            }
        } else {
            //节点已存在，不进行任何操作
            return tree;
        }
        tree->height = max(tree_height(tree->left), tree_height(tree->right)) + 1;
        return tree;
    }

    static TreeNode *tree_delete_node(TreeNode *tree, TreeNode *z) {
        if (tree == nullptr || z == nullptr) return nullptr;
        //待删除的节点在tree的左子树中
        if (z->val < tree->val) {
            tree->left = tree_delete_node(tree->left, z);
            //删除节点后，若AVL树失去平衡，则进行相应的调整
            if (tree_height(tree->right) - tree_height(tree->left) == 2) {
                if (tree_height(tree->right->right) > tree_height(tree->right->left)) {
                    tree = right_right_rotation(tree);
                } else {
                    tree = right_left_rotation(tree);
                }
            }
        } else if (z->val > tree->val) {
            //待删除的节点在tree的右子树中
            tree->right = tree_delete_node(tree->right, z);
            //删除节点后，若AVL树失去平衡，则进行相应的调整
            if (tree_height(tree->left) - tree_height(tree->right) == 2) {
                if (tree_height(tree->left->left) > tree_height(tree->left->right)) {
                    tree = left_left_rotation(tree);
                } else {
                    tree = left_right_rotation(tree);
                }
            }
        } else {
            //一般实现，对照二叉搜索树的删除节点的实现
//            //z是当前节点
//            if (tree->left == nullptr && tree->right == nullptr) {
//                //z是叶子节点
//                delete tree;
//                tree = nullptr;
//            } else if (tree->left == nullptr) {
//                //z只有一个右子树
//                TreeNode *temp = tree;
//                tree = tree->right;
//                delete temp;
//            } else if (tree->right == nullptr) {
//                //z只有一个左子树
//                TreeNode *temp = tree;
//                tree = tree->left;
//                delete temp;
//            } else {
//                //z有两个子树
//                //找到z右侧子树中的最小节点，将其值赋给z节点，然后删除最小节点
//                TreeNode *temp = tree->right;
//                while (temp->left != nullptr) {
//                    temp = temp->left;
//                }
//                tree->val = temp->val;
//                tree->right = tree_delete_node(tree->right, temp);
//                if (tree_height(tree->left) - tree_height(tree->right) == 2) {
//                    if (tree_height(tree->left->left) > tree_height(tree->left->right)) {
//                        tree = left_left_rotation(tree);
//                    } else {
//                        tree = left_right_rotation(tree);
//                    }
//                }
//            }
            //高效实现，对于有左右孩子的节点，通过两种判断方式，选择删除节点的方式，从而减少旋转次数
            if (tree->left != nullptr && tree->right != nullptr) {
                if (tree_height(tree->left) > tree_height(tree->right)) {
                    // 如果tree的左子树比右子树高；
                    // 则(01)找出tree的左子树中的最大节点
                    //   (02)将该最大节点的值赋值给tree。
                    //   (03)删除该最大节点。
                    // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                    // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                    TreeNode *max = tree_maximum(tree->left);
                    tree->val = max->val;
                    tree->left = tree_delete_node(tree->left, max);
                } else {
                    // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                    // 则(01)找出tree的右子树中的最小节点
                    //   (02)将该最小节点的值赋值给tree。
                    //   (03)删除该最小节点。
                    // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                    // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                    TreeNode *min = tree_minimum(tree->right);
                    tree->val = min->val;
                    tree->right = tree_delete_node(tree->right, min);
                }
            } else {
                TreeNode *tmp = tree;
                tree = tree->left != nullptr ? tree->left : tree->right;
                delete tmp;
            }
        }
        return tree;
    }

    void destroy_tree(TreeNode *tree) {
        if (tree == nullptr) return;
        if (tree->left != nullptr) destroy_tree(tree->left);
        if (tree->right != nullptr) destroy_tree(tree->right);
        delete tree;
    }


private:
    TreeNode *root;
};

#endif //AVL_AVL_H
