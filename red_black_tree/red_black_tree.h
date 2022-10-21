//
// Created by admin on 2022/10/20.
//

#ifndef RED_BACK_TREE_RED_BLACK_TREE_H
#define RED_BACK_TREE_RED_BLACK_TREE_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class red_black_tree {
private:
    enum Color {
        RED, BLACK
    };

    struct Node {
        Color color;
        int key;
        Node *left;
        Node *right;
        Node *parent;

        explicit Node() : color(BLACK), key(0), left(nullptr), right(nullptr), parent(nullptr) {}

        explicit Node(int key) : color(RED), key(key), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root = nullptr;
    Node *nil = nullptr;

    void leftRotate(Node *node) {
        if (node == nil || node->right == nil) {
            return;
        }
        Node *right = node->right;
        node->right = right->left;
        if (right->left != nil) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if (node->parent == nullptr) {
            // node is root
            root = right;
        } else if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
    }

    void rightRotate(Node *node) {
        if (node == nil || node->left == nil) {
            return;
        }
        Node *left = node->left;
        node->left = left->right;
        if (left->right != nil) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if (node->parent == nullptr) {
            // node is root
            root = left;
        } else if (node == node->parent->left) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }
        left->right = node;
        node->parent = left;
    }

    void insertFix(Node *node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                // Left
                Node *uncle = node->parent->parent->right;
                if (uncle != nil && uncle->color == RED) {
                    // case 1: uncle is red(existed)
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    // case 2: uncle is black(nil)
                    if (node == node->parent->right) {
                        // Left-Right to Left-Left
                        // case 2.1: node is right child
                        node = node->parent;
                        leftRotate(node);
                    }
                    // Left-Left
                    // case 2.2: node is left child
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                // Right
                Node *uncle = node->parent->parent->left;
                if (uncle != nil && uncle->color == RED) {
                    // case 1: uncle is red
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    // case 2: uncle is black
                    if (node == node->parent->left) {
                        // Right-Left to Right-Right
                        // case 2.1: node is left child
                        node = node->parent;
                        rightRotate(node);
                    }
                    // Right-Right
                    // case 2.2: node is right child
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void removeFix(Node *node) {
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                // Left
                Node *brother = node->parent->right;
                if (brother->color == RED) {
                    // case 1: brother is red
                    brother->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    brother = node->parent->right;
                }
                if (brother->left->color == BLACK && brother->right->color == BLACK) {
                    // case 2: brother is black and both children are black
                    brother->color = RED;
                    node = node->parent;
                } else {
                    if (brother->right->color == BLACK) {
                        // Right-Left to Right-Right
                        // case 3: brother is black and left child is red
                        brother->left->color = BLACK;
                        brother->color = RED;
                        rightRotate(brother);
                        brother = node->parent->right;
                    }
                    // case 4: brother is black and right child is red
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother->right->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            } else {
                // Right
                Node *brother = node->parent->left;
                if (brother->color == RED) {
                    // case 1: brother is red
                    brother->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    brother = node->parent->left;
                }
                if (brother->left->color == BLACK && brother->right->color == BLACK) {
                    // case 2: brother is black and both children are black
                    brother->color = RED;
                    node = node->parent;
                } else {
                    if (brother->left->color == BLACK) {
                        // Left-Right to Left-Left
                        // case 3: brother is black and right child is red
                        brother->right->color = BLACK;
                        brother->color = RED;
                        leftRotate(brother);
                        brother = node->parent->left;
                    }
                    // case 4: brother is black and left child is red
                    brother->color = node->parent->color;
                    node->parent->color = BLACK;
                    brother = node->parent->left;
                    brother->left->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    void printRBTree(Node *node, string indent, bool last) {
        if (node != nil) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            string sColor = node->color == RED ? "RED" : "BLACK";
            cout << node->key << "(" << sColor << ")" << endl;
            printRBTree(node->left, indent, false);
            printRBTree(node->right, indent, true);
        }
    }

public:
    red_black_tree() {
        nil = new Node();
        root = nil;
    }

    void insert(int key) {
        Node *node = new Node(key);
        node->left = nil;
        node->right = nil;
        if (root == nil) {
            root = node;
            root->color = BLACK;
        } else {
            Node *temp = root;
            while (temp != nil) {
                if (key < temp->key) {
                    if (temp->left != nil) {
                        temp = temp->left;
                    } else {
                        temp->left = node;
                        node->parent = temp;
                        break;
                    }
                } else if (key > temp->key) {
                    if (temp->right != nil) {
                        temp = temp->right;
                    } else {
                        temp->right = node;
                        node->parent = temp;
                        break;
                    }
                } else {
                    // key == temp->key
                    return;
                }
            }
            insertFix(node);
        }
    }

    void remove(int key) {
        if (root == nil) {
            return;
        }
        Color originalColor;
        Node *node = root, *z = nil;
        while (node != nil) {
            if (key < node->key) {
                node = node->left;
            } else if (key > node->key) {
                node = node->right;
            } else {
                z = node;
                break;
            }
        }
        if (z == nil) {
            return;
        }

        originalColor = node->color;
        // case 1: node has no left child or has no children
        if (node->left == nil) {
            Node *temp = node->right;
            if (node->parent == nullptr) {
                // node is root
                root = temp;
            } else if (node == node->parent->left) {
                node->parent->left = temp;
            } else {
                node->parent->right = temp;
            }
            temp->parent = node->parent;
            delete node;
            node = temp;
        } else if (node->right == nil) {
            // case 2: node has no right child
            Node *temp = node->left;
            if (node->parent == nullptr) {
                // node is root
                root = temp;
            } else if (node == node->parent->left) {
                node->parent->left = temp;
            } else {
                node->parent->right = temp;
            }
            temp->parent = node->parent;
            delete node;
            node = temp;
        } else {
            // case 3: node has both left and right child
            // find the minimum of right subtree
            Node *temp = node->right;
            while (temp->left != nil) {
                temp = temp->left;
            }
            // exchange key
            node->key = temp->key;
            // now temp is the node to be deleted
            node = temp;
            originalColor = node->color;
            // right child of temp should be the child of temp's parent
            Node *temp2 = node->right;
            if (node->parent == nullptr) {
                // node is root
                root = temp2;
            } else if (node == node->parent->left) {
                node->parent->left = temp2;
            } else {
                node->parent->right = temp2;
            }
            temp2->parent = node->parent;
            delete node;
            node = temp2;
        }
        if (originalColor == BLACK) {
            removeFix(node);
        }
    }

    void printTree() {
        printRBTree(root, "", true);
    }

    void minimum() {
        Node *node = root;
        while (node->left != nil) {
            node = node->left;
        }
        cout << "Minimum: " << node->key << endl;
    }

    void maximum() {
        Node *node = root;
        while (node->right != nil) {
            node = node->right;
        }
        cout << "Maximum: " << node->key << endl;
    }
    Node* search(int key) {
        Node *node = root;
        while (node != nil) {
            if (key < node->key) {
                node = node->left;
            } else if (key > node->key) {
                node = node->right;
            } else {
                return node;
            }
        }
        return nullptr;
    }
};


#endif //RED_BACK_TREE_RED_BLACK_TREE_H
