#include "link_list.h"

void test1();

void test2();

void test3();

void test4();

int main() {
//    test1();
//    test2();
    test3();
//    test4();
    return 0;
}

void test1() {
    LinkList<int> list;
    int n;
    std::cout << "请输入链表中有几个值： ";
    std::cin >> n;
    std::cout << "请输入链表中存放的值： ";
    int data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        list.insert(list.length(), data);
    }
    list.display();
    list.sort([](const int &a, const int &b) -> bool {
        return a < b;
    });
    list.display();
}

void test2() {
    LinkList<int> list, list1;
    int n;
    std::cout << "请输入链表1有几个值： ";
    std::cin >> n;
    std::cout << "请输入链表1中存放的值： ";
    int data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        list.insert(list.length(), data);
    }
    std::cout << "请输入链表2中有几个值： ";
    std::cin >> n;
    std::cout << "请输入链表2中存放的值： ";
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        list1.insert(list1.length(), data);
    }
    list.display();
    list1.display();
    list.mergeByDescending(list1);
    list.display();
}

void test3() {
    LinkList<int> list;
    int n;
    std::cout << "请输入链表中有几个值： ";
    std::cin >> n;
    std::cout << "请输入链表中存放的值： ";
    int data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        list.insert(list.length(), data);
    }
    list.display();
    list.dispatch();
    list.display();
}

void test4() {
    LinkList<int> list;
    int n;
    std::cout << "请输入链表中有几个值： ";
    std::cin >> n;
    std::cout << "请输入链表中存放的值： ";
    int data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        list.insert(list.length(), data);
    }
    list.display();
    int k;
    std::cout << "请输入需要查找的链表倒数第k个值: ";
    std::cin >> k;
    std::cout << list.reverseNoK(k)->data;
}