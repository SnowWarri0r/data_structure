//
// Created by SnowWarrior on 2021/11/18.
//

#ifndef SEQUENCE_STACK_SEQUENCESTACK_H
#define SEQUENCE_STACK_SEQUENCESTACK_H

#include <iostream>

constexpr int INIT_SIZE = 16;
constexpr int INCREMENT_SIZE = 8;

template<typename T>
class SequenceStack {
public:
    SequenceStack() : size(INIT_SIZE) {
        bottom = new T[INIT_SIZE + 1];
        if (bottom == nullptr) throw std::runtime_error("allocating memory for stack error!");
        sp = bottom + 1;
    }

    ~SequenceStack() {
        delete[] bottom;
        size = 0;
        sp = nullptr;
        bottom = nullptr;
    }

    int length() const { return sp - bottom - 1; }

    bool empty() const { return length() == 0; }

    bool push(T data) {
        if (length() >= size) {
            T *newBase = new T[size + INCREMENT_SIZE];
            if (newBase == nullptr) throw std::runtime_error("allocating memory for stack error!");
            T *newSp = newBase + 1;
            for (int i = 1; i < size; ++i) {
                *(newBase + i) = *(bottom + i);
                newSp++;
            }
            bottom = newBase;
            sp = newSp;
        }
        *sp = data;
        sp++;
        return true;
    }

    void clear() {
        sp = bottom + 1;
    }

    T top() const {
        return *(sp - 1);
    }

    bool pop() {
        if (empty()) return false;
        sp--;
        return true;
    }

    void display() const {
        T *p = sp;
        while (--p != bottom) std::cout << *p << std::endl;
    }

private:
    T *bottom;
    T *sp;
    int size;
};

#endif //SEQUENCE_STACK_SEQUENCESTACK_H
