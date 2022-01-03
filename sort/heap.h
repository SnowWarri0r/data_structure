//
// Created by SnowWarrior on 2022/1/3.
//

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

#include <iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;
constexpr static int HEAP_DEFAULT_SIZE = 50;

class heap {
public:
    explicit heap(int sz = HEAP_DEFAULT_SIZE) {
        maxSize = sz < HEAP_DEFAULT_SIZE ? HEAP_DEFAULT_SIZE : sz;
        head = new int[maxSize];
        curSize = 0;
    }

    explicit heap(const vector<int> &arr) {
        int n = (int) arr.size();
        maxSize = n < HEAP_DEFAULT_SIZE ? HEAP_DEFAULT_SIZE : n;
        head = new int[maxSize];
        for (int i = 0; i < n; ++i) {
            head[i] = arr[i];
        }
        curSize = n;
        int curPos = (curSize - 2) / 2;
        while (curPos >= 0) {
            siftDown(curPos, curSize - 1);
            curPos--;
        }
    }

    bool insert(const int &x) {
        if (curSize == maxSize) {
            cout << "Heap is full!" << endl;
            return false;
        }
        head[curSize] = x;
        siftUp(curSize);
        curSize++;
        return true;
    }

    bool remove(int &x) {
        if (!curSize) {
            cout << "Heap empty!" << endl;
            return false;
        }
        x = head[0];
        head[0] = head[curSize - 1];
        curSize--;
        siftDown(0, curSize - 1);
        return true;
    }

private:
    void siftDown(int start, int end) {
        int cur = start;
        int min_child = start * 2 + 1;
        int temp = head[cur];
        while (min_child <= end) {
            if (min_child < end && head[min_child] > head[min_child + 1]) {
                min_child++;
            }
            if (temp <= head[min_child]) {
                break;
            } else {
                head[cur] = head[min_child];
                cur = min_child;
                min_child = min_child * 2 + 1;
            }
        }
        head[cur] = temp;
    }

    void siftUp(int start) {
        int cur = start;
        int parent = (cur - 1) / 2;
        int temp = head[cur];
        while (cur > 0) {
            if (head[parent] <= temp) {
                break;
            } else {
                head[cur] = head[parent];
                cur = parent;
                parent = (parent - 1) / 2;
            }
        }
        head[cur] = temp;
    }

private:
    int *head;
    int curSize;
    int maxSize;
};


#endif //SORT_HEAP_H
