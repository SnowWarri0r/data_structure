//
// Created by SnowWarrior on 2021/11/25.
//

#ifndef STACK_SIMULATE_QUEUE_QUEUESIMULATOR_H
#define STACK_SIMULATE_QUEUE_QUEUESIMULATOR_H

#include <stack>
#include<iostream>

using std::stack;

template<typename T>
class QueueSimulator {
public:
    QueueSimulator() = default;

    void enqueue(T elem) {
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        s1.push(elem);
    }

    void dequeue(T &elem) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        elem = s2.top();
        s2.pop();
    }

    bool empty() const {
        return s1.size() + s2.size() == 0;
    }

    void display() {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        stack<int> clone1 = stack<T>(s2);
        while (!s2.empty()) {
            std::cout << s2.top() << " ";
            s2.pop();
        }
        std::cout << std::endl;
        s2 = clone1;
    }

private:
    stack<T> s1;
    stack<T> s2;
};

#endif //STACK_SIMULATE_QUEUE_QUEUESIMULATOR_H
