#include <iostream>
#include <unordered_set>
#include "sequence_list.h"

using std::unordered_set;

void classify(const sequence_list<int> &l1, sequence_list<int> &l2, sequence_list<int> &l3);

void partition(sequence_list<int> &list);

void inter(const sequence_list<int> &a, const sequence_list<int> &b, sequence_list<int> &c);

void merge(const sequence_list<int> &l1, const sequence_list<int> &l2, sequence_list<int> &l3);

template<typename T>
void reverse(sequence_list<T> &list);

int main() {
    //target1
    int arr1[]{1, 2, 5, 4, 3, 5, 6, 7, 8, 54, 3, 21, 42, 564, 643, 241, 124, 424, 21};
    sequence_list<int> l1(arr1, 19), l2, l3;
    int res;
    std::cout << "classify函数调用前:\nl1:\n";
    for (int i = 0; i < l1.length(); ++i) {
        l1.get(i, res);
        std::cout << res << " ";
    }
    classify(l1, l2, l3);
    std::cout << "\nclassify函数调用后:\nl2:\n";
    for (int i = 0; i < l2.length(); ++i) {
        l2.get(i, res);
        std::cout << res << " ";
    }
    std::cout << "\nl3:\n";
    for (int i = 0; i < l3.length(); ++i) {
        l3.get(i, res);
        std::cout << res << " ";
    }
    //target2
    int arr[]{3, 241, 41, 41, 22, 43, 42, 21, 90, 31, 21, 50, 30, 75};
    sequence_list<int> list(arr, 14);
    list.insert(0, 5);
    list.insert(1, 7);

    std::cout << "\npartition函数调用前:\n";
    for (int i = 0; i < list.length(); ++i) {
        list.get(i, res);
        std::cout << res << " ";
    }
    partition(list);
    std::cout << "\npartition函数调用后:\n";
    for (int i = 0; i < list.length(); ++i) {
        list.get(i, res);
        std::cout << res << " ";
    }

    //target3
    int a[]{1, 5, 7, 2, 4};
    int b[]{2, 4, 7, 9, 10};
    sequence_list<int> listA(a, 5), listB(b, 5), listC;
    std::cout << "\n列表a:\n";
    for (int i = 0; i < listA.length(); ++i) {
        listA.get(i, res);
        std::cout << res << " ";
    }
    std::cout << "\n列表b:\n";
    for (int i = 0; i < listB.length(); ++i) {
        listB.get(i, res);
        std::cout << res << " ";
    }
    std::cout << "\n列表a和b的交集:\n";
    inter(listA, listB, listC);
    for (int i = 0; i < listC.length(); ++i) {
        listC.get(i, res);
        std::cout << res << " ";
    }

    //target4
    int a1[]{1, 5, 7, 13, 15, 17, 20, 35, 40, 43, 67};
    int a2[]{4, 8, 17, 29, 31, 50, 79};
    sequence_list<int> list1(a1, 11), list2(a2, 7), list3;
    std::cout << "\n合并前:\nl1:\n";
    for (int i = 0; i < list1.length(); ++i) {
        list1.get(i, res);
        std::cout << res << " ";
    }
    std::cout << "\nl2:\n";
    for (int i = 0; i < list2.length(); ++i) {
        list2.get(i, res);
        std::cout << res << " ";
    }
    merge(list1, list2, list3);
    std::cout << "\n合并后:\nl3:\n";
    for (int i = 0; i < list3.length(); ++i) {
        list3.get(i, res);
        std::cout << res << " ";
    }
    //target5

    int array[]{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25};
    sequence_list<int> sList(array, 13);
    std::cout << "\n反转前:\n";
    for (int i = 0; i < sList.length(); ++i) {
        sList.get(i, res);
        std::cout << res << " ";
    }
    reverse(sList);
    std::cout << "\n反转后:\n";
    for (int i = 0; i < sList.length(); ++i) {
        sList.get(i, res);
        std::cout << res << " ";
    }
    return 0;
}

void classify(const sequence_list<int> &l1, sequence_list<int> &l2, sequence_list<int> &l3) {
    int val;
    for (int i = 0; i < l1.length(); ++i) {
        l1.get(i, val);
        if (val % 2 == 0) {
            l3.insert(l3.length(), val);
        } else {
            l2.insert(l2.length(), val);
        }
    }
}

//O(n)的时间复杂度
void partition(sequence_list<int> &list) {
    int l = 0, r = list.length() - 1;
    while (l < r) {
        int lVal, rVal;
        while (l < r) {
            list.get(l, lVal);
            if (lVal % 2 == 0) break;
            l++;
        }
        while (r > l) {
            list.get(r, rVal);
            if ((rVal - 1) % 2 == 0) break;
            r--;
        }
        list.set(r, lVal);
        list.set(l, rVal);
    }
}

void inter(const sequence_list<int> &a, const sequence_list<int> &b, sequence_list<int> &c) {
    unordered_set<int> uset;
    int val;
    for (int i = 0; i < a.length(); ++i) {
        a.get(i, val);
        uset.insert(val);
    }
    for (int i = 0; i < b.length(); ++i) {
        b.get(i, val);
        auto p = uset.insert(val);
        if (!p.second) c.insert(c.length(), val);
    }
}

void merge(const sequence_list<int> &l1, const sequence_list<int> &l2, sequence_list<int> &l3) {
    int val1, val2;
    int p1 = 0, p2 = 0;
    while (p1 < l1.length() && p2 < l2.length()) {
        l1.get(p1, val1);
        l2.get(p2, val2);
        if (val1 < val2) {
            l3.insert(l3.length(), val1);
            p1++;
        } else {
            l3.insert(l3.length(), val2);
            p2++;
        }
    }
    while (p1 < l1.length()) {
        l3.insert(l3.length(), val1);
        p1++;
    }
    while (p2 < l2.length()) {
        l3.insert(l3.length(), val2);
        p2++;
    }
}

template<typename T>
void reverse(sequence_list<T> &list) {
    int l = 0, r = list.length() - 1;
    int val1, val2;
    while (l < r) {
        list.get(r, val1);
        list.get(l, val2);
        list.set(l, val1);
        list.set(r, val2);
        l++;
        r--;
    }
}