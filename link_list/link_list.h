//
// Created by SnowWarrior on 2021/11/4.
//

#ifndef LINK_LIST_LINK_LIST_H
#define LINK_LIST_LINK_LIST_H

template<typename T>
struct node {
    T data;
    node *next;

    explicit node(T data = NULL) {
        this->data = data;
        next = nullptr;
    }

    explicit node(node *next, T data = NULL) {
        this->data = data;
        this->next = next;
    }
};

template<typename T>
class link_list {
public:
    link_list() : len(0), head(nullptr) {
    }

    explicit link_list(T data = NULL) : len(1) {
        head = new node<T>(nullptr, data);
    }

    ~link_list() {
        clear();
    }

    void clear() {
        auto *p = head;
        auto *q = p;
        while (p->next != nullptr) {
            p = p->next;
            delete q;
            q = p;
        }
        delete q;
        len = 0;
    }

    int length() const { return len; }

    bool empty() const { return len == 0; }

    bool insert(int index, T data) {
        if (index < 0 || index > len) return false;
        if (index == 0) {
            auto *newNode = new node<T>(head, data);
            head = newNode;
        } else {
            auto *prev = head, *cur = head->next;
            for (int i = 0; i < index - 1; ++i) {
                prev = prev->next;
                cur = cur->next;
            }
            auto *newNode = new node<T>(cur, data);
            prev->next = newNode;
        }
        len++;
        return true;
    }

    bool erase(int index, T &data) {
        if (index < 0 || index >= len) return false;
        if (index == 0) {
            data = head->data;
            auto *p = head;
            head = head->next;
            delete p;
        } else {
            auto *prev = head;
            auto *cur = head->next;
            for (int i = 0; i < index - 1; ++i) {
                prev = prev->next;
                cur = cur->next;
            }
            prev->next = cur->next;
            data = cur->data;
            delete cur;
        }
        len--;
        return true;
    }

public:
    T get(int index) {
        if (index < 0 || index >= len) return (T) NULL;
        auto *cur = head;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->data;
    }

    bool set(int index, T data) {
        if (index < 0 || index >= len) return false;
        auto *cur = head;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        cur->data = data;
        return true;
    }


private:
    node<T> *head;
    int len;
};

#endif //LINK_LIST_LINK_LIST_H
