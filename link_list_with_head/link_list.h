//
// Created by SnowWarrior on 2021/11/11.
//

#ifndef LINK_LIST_WITH_HEAD_LINK_LIST_H
#define LINK_LIST_WITH_HEAD_LINK_LIST_H

#include <iostream>

template<typename T>
struct Node {
    T data;
    Node *next;

    explicit Node(T data = (T) NULL) : data(data), next(nullptr) {}

    Node(T data, Node *node) : data(data), next(node) {}
};

template<typename T>
class LinkList {
public:
    LinkList() : len(0) {
        head = new Node<T>();
        tail = head;
    }

    explicit LinkList(T data) : len(1) {
        auto *node = new Node<T>(data);
        head = new Node<T>(NULL, node);
        tail = node;
    }

    bool insert(int index, T data) {
        if (index < 0 || index > len) return false;
        if (index == len) {
            auto *node = new Node<T>(data);
            if (node == nullptr) throw std::runtime_error("allocating memory for node failed");
            tail->next = node;
            tail = node;
            len++;
            return true;
        }
        auto *cur = head->next;
        auto *prev = head;
        for (int i = 0; i < index; ++i) {
            prev = prev->next;
            cur = cur->next;
        }
        auto *node = new Node<T>(data, cur);
        if (node == nullptr) throw std::runtime_error("allocating memory for node failed");
        prev->next = node;
        len++;
        return true;
    }

    bool erase(int index, T &data) {
        if (index < 0 || index >= len) return false;
        if (index == len - 1) {
            data = tail->data;
            auto *p = head;
            while (p->next != tail) {
                p = p->next;
            }
            delete tail;
            tail = p;
            tail->next = nullptr;
            len--;
            return true;
        }
        auto *prev = head;
        auto *cur = head->next;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
            prev = prev->next;
        }
        prev->next = cur->next;
        data = cur->data;
        delete cur;
        len--;
        return true;
    }

    bool empty() const {
        return len == 0;
    }

    int length() const {
        return len;
    }

    void display() const {
        auto *p = head;
        while (p->next != nullptr) {
            p = p->next;
            std::cout << p->data << " ";
        }
        std::cout << std::endl;
    }

    void sort(std::function<bool(const T &a, const T &b)> cmp) {
        for (int subLength = 1; subLength < len; subLength <<= 1) {
            Node<T> *prev = head, *curr = head->next;
            while (curr != nullptr) {
                Node<T> *head1 = curr;
                for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                Node<T> *head2 = curr->next;
                curr->next = nullptr;
                curr = head2;
                for (int i = 1; i < subLength && curr != nullptr && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                Node<T> *next = nullptr;
                if (curr != nullptr) {
                    next = curr->next;
                    curr->next = nullptr;
                }
                Node<T> *merged = merge(head1, head2, cmp);
                prev->next = merged;
                while (prev->next != nullptr) {
                    prev = prev->next;
                }
                curr = next;
            }
        }
    }

    void reverse() {
        if (len == 1) return;
        if (len == 2) {
            head->next->next->next = head->next;
            head->next->next = nullptr;
            head->next = tail;
            tail = head->next->next;
        }
        Node<T> *first = head->next, *mid = head->next->next, *last = head->next->next->next;


    }

    void mergeByDescending(Node<T> *list) {

    }

private:
    Node<T> *merge(Node<T> *head1, Node<T> *head2, std::function<bool(const T &a, const T &b)> cmp) {
        if (head1 == nullptr) return head2;
        if (head2 == nullptr) return head1;

        Node<T> *curHead = nullptr, *p = nullptr;
        while (head1 != nullptr && head2 != nullptr) {
            if (curHead == nullptr) {
                if (cmp(head1->data, head2->data)) {
                    curHead = head1;
                    head1 = head1->next;
                } else {
                    curHead = head2;
                    head2 = head2->next;
                }
                p = curHead;
            } else {
                if (cmp(head1->data, head2->data)) {
                    p->next = head1;
                    head1 = head1->next;
                } else {
                    p->next = head2;
                    head2 = head2->next;
                }
                p = p->next;
            }
        }
        if (head1 != nullptr) p->next = head1;
        else p->next = head2;
        return curHead;
    }
//    Node<T> *listSort(Node<T> *node, std::function<bool(const T &a, const T &b)> cmp) {
//        if (node == nullptr || node->next == nullptr) return node;
//
//        Node<T> *mid = getMidNode(node);
//        Node<T> *left = node;
//        Node<T> *right = mid->next;
//        mid->next = nullptr;
//        return merge(listSort(left, cmp), listSort(right, cmp), cmp);
//    }
//
//    Node<T> *merge(Node<T> *left, Node<T> *right, std::function<bool(const T &a, const T &b)> &cmp) {
//        if (left == nullptr) return right;
//        if (right == nullptr) return left;
//
//        Node<T> *curHead = nullptr, *p = nullptr;
//        while (left != nullptr && right != nullptr) {
//            if (curHead == nullptr) {
//                if (cmp(left->data, right->data)) {
//                    curHead = left;
//                    left = left->next;
//                } else {
//                    curHead = right;
//                    right = right->next;
//                }
//                p = curHead;
//            } else {
//                if (cmp(left->data, right->data)) {
//                    p->next = left;
//                    left = left->next;
//                } else {
//                    p->next = right;
//                    right = right->next;
//                }
//                p = p->next;
//            }
//        }
//        if (left != nullptr) p->next = left;
//        else p->next = right;
//        return curHead;
//    }
//
//    Node<T> *getMidNode(Node<T> *node) const {
//        if (node == nullptr || node->next == nullptr) return node;
//        auto *low = node;
//        auto *fast = node;
//        while (fast->next != nullptr && fast->next->next != nullptr) {
//            low = low->next;
//            fast = fast->next->next;
//        }
//        return low;
//    }

private:
    int len;
    Node<T> *head;
    Node<T> *tail;
};

#endif //LINK_LIST_WITH_HEAD_LINK_LIST_H
