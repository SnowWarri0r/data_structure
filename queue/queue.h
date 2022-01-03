//
// Created by SnowWarrior on 2022/1/3.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <iostream>

constexpr static int QUEUE_DEFAULT_SIZE = 16;
constexpr static int QUEUE_INCREMENT_SIZE = 8;

template<typename T>
class queue {
public:
    queue() : sz(QUEUE_DEFAULT_SIZE), len(0) {
        base = new T[QUEUE_DEFAULT_SIZE];
        if (base == nullptr) throw std::runtime_error("allocating memory for queue error");
        bk = -1, ft = 0;
    }

    void push(const T &val) {
        if (len >= sz) {
            T *newBase = new T[sz + QUEUE_INCREMENT_SIZE];
            if (newBase == nullptr) {
                throw std::runtime_error("allocating memory for queue error");
            }
            int index = 0;
            while (index < len) {
                newBase[index] = base[(ft + index) % sz];
                index++;
            }
            sz += QUEUE_INCREMENT_SIZE;
            base = newBase;
            ft = 0;
            bk = ft + len - 1;
        }
        bk = (bk + 1) % sz;
        base[bk] = val;
        len++;
    }

    bool pop() {
        if (empty()) return false;
        ft = (ft + 1) % sz;
        len--;
        return true;
    }

    inline T front() const { return base[ft]; }

    inline T back() const { return base[bk]; }

    inline bool empty() const {
        return len == 0;
    }

    inline int size() const { return len; }

    inline void display() const {
        int p = ft;
        while (p != bk) {
            std::cout << base[p] << " ";
            p = (p + 1) % sz;
        }
        std::cout << base[p] << std::endl;
    }

private:
    T *base;
    int ft;
    int bk;
    int sz;
    int len;
};

#endif //QUEUE_QUEUE_H
