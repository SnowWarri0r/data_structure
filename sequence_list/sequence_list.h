//
// Created by admin on 2021/10/30.
//
#include<vector>

#ifndef SEQUENCE_LIST_SEQUENCE_LIST_H
#define SEQUENCE_LIST_SEQUENCE_LIST_H
const int LIST_INIT_SIZE = 20;
const int LIST_INCREMENT_SIZE = 10;

template<typename T>
class sequence_list {
public:
    sequence_list() {
        elem = new T[LIST_INIT_SIZE];
        if (elem == nullptr) throw std::runtime_error("allocating memory for sequence list failed");
        len = 0;
        size = LIST_INIT_SIZE;
    };

    sequence_list(T elems[], int n) {
        int initSize;
        if (n > LIST_INIT_SIZE) {
            initSize = n / 10 + LIST_INCREMENT_SIZE;
            elem = new T[initSize];
            size = initSize;
        } else {
            initSize = LIST_INIT_SIZE;
            elem = new T[initSize];
        }
        if (elem == nullptr) throw std::runtime_error("allocating memory for sequence list failed");
        for (int i = 0; i < n; ++i) {
            elem[i] = elems[i];
        }
        len = n;
        size = initSize;
    }

    ~sequence_list() {
        delete[] elem;
    }

    bool empty() { return len == 0; }

    int length() const { return len; }

    bool get(int index, T &e) const {
        if (index < 0 || index >= len) return false;
        e = elem[index];
        return true;
    };

    bool set(int index, T e) {
        if (index < 0 || index >= len) return false;
        elem[index] = e;
        return true;
    }

    bool insert(int index, T e) {
        if (index < 0 || index > len) return false;
        if (len >= size) {
            T *newBase = new T[size + LIST_INCREMENT_SIZE];
            if (newBase == nullptr) throw std::runtime_error("allocating memory for sequence list failed");
            for (int i = 0; i < len; ++i) {
                newBase[i] = elem[i];
            }
            delete[] elem;
            elem = newBase;
            size += LIST_INCREMENT_SIZE;
        }
        T *q = &(elem[index]);
        for (T *p = &(elem[len - 1]); p >= q; p--) *(p + 1) = *p;
        *q = e;
        len++;
        return true;
    }

    bool erase(int index, T &e) {
        if (index < 0 || index >= len) return false;
        T *p = &(elem[index]);
        e = *p;
        T *q = elem + len - 1;
        for (++p; p <= q; ++p) *(p - 1) = *p;
        len--;
        return true;
    }

    void clear() {
        len = 0;
    }

//public:
//    T &operator[](int index) {
//        return elem[index];
//    }
//
//    const int &operator[](int index) const {
//        return elem[index];
//    }

private:
    T *elem;
    int len;
    int size;
};

#endif //SEQUENCE_LIST_SEQUENCE_LIST_H
