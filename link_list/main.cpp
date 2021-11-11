#include "link_list.h"

void insertByAscending(link_list<int> &list, int data);

void deleteAll(link_list<int> &list, int val);

void deleteLast(link_list<int> &list, int val);

//void reverse(link_list<int> &list);

int main() {
    //target1
    link_list<int> list(5);
    list.insert(list.length(), 7);
    list.insert(list.length(), 9);
    list.insert(list.length(), 13);
    list.insert(list.length(), 17);
    list.insert(list.length(), 18);
    list.insert(list.length(), 20);
    for (int i = 0; i < list.length(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    insertByAscending(list, 19);
    for (int i = 0; i < list.length(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    insertByAscending(list, 2);
    for (int i = 0; i < list.length(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    insertByAscending(list, 30);
    for (int i = 0; i < list.length(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl;
    //target2
    link_list<int> list1(5);
    list1.insert(list1.length(), 5);
    list1.insert(list1.length(), 7);
    list1.insert(list1.length(), 7);
    list1.insert(list1.length(), 7);
    list1.insert(list1.length(), 7);
    list1.insert(list1.length(), 7);
    for (int i = 0; i < list1.length(); ++i) {
        std::cout << list1.get(i) << " ";
    }
    std::cout << std::endl;
    deleteAll(list1, 7);
    for (int i = 0; i < list1.length(); ++i) {
        std::cout << list1.get(i) << " ";
    }
    std::cout << std::endl;
    //target3
    link_list<int> list2(7);
    list2.insert(list2.length(), 9);
    list2.insert(list2.length(), 9);
    list2.insert(list2.length(), 9);
    list2.insert(list2.length(), 10);
    list2.insert(list2.length(), 9);
    list2.insert(list2.length(), 9);
    list2.insert(list2.length(), 10);
    list2.insert(list2.length(), 9);
    for (int i = 0; i < list2.length(); ++i) {
        std::cout << list2.get(i) << " ";
    }
    std::cout << std::endl;
    deleteLast(list2, 10);
    for (int i = 0; i < list2.length(); ++i) {
        std::cout << list2.get(i) << " ";
    }
    std::cout << std::endl;
    list.display();
    std::cout << std::endl;
    list.reverse();
    list.display();
    return 0;
}

void insertByAscending(link_list<int> &list, int data) {
    int index = 0;
    while (index < list.length() && list.get(index) < data) index++;
    list.insert(index, data);
}

void deleteAll(link_list<int> &list, int val) {
    int index = 0;
    while (index < list.length()) {
        int data;
        if (list.get(index) == val) {
            list.erase(index, data);
            continue;
        }
        index++;
    }
}

void deleteLast(link_list<int> &list, int val) {
    int p = -1;
    for (int i = 0; i < list.length(); ++i) {
        if (list.get(i) == val) p = i;
    }
    int data;
    list.erase(p, data);
}

//void reverse(link_list<int> &list) {
//    int l, r;
//    int n = list.length();
//    if (n % 2 == 1) {
//        l = (n - 1) / 2 - 1;
//        r = (n + 1) / 2 - 1;
//    } else {
//        l = n / 2 - 1;
//        r = l + 1;
//    }
//    while (r < n) {
//        int lVal = list.get(l);
//        int rVal = list.get(r);
//        list.set(r, lVal);
//        list.set(l, rVal);
//        l--;
//        r++;
//    }
//}