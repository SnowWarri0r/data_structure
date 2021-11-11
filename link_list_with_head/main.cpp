#include "link_list.h"

int main() {
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
    return 0;
}
