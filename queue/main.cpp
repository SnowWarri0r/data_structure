#include "queue.h"
#include <stack>

using namespace std;

void reverse(queue<int> &queue);

void test1();

void test0();

int main() {
    test0();
//    test1();
    return 0;
}

void test0() {
    queue<int> queue;
    cout << "请输入要保存进队列的元素个数：";
    int n;
    cin >> n;
    cout << "请输入元素：";
    int elem;
    for (int i = 0; i < n; ++i) {
        cin >> elem;
        queue.push(elem);
    }
    queue.display();
    cout << "请输入要删除队列的元素个数：";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        queue.pop();
    }
    cout << "请输入要保存进队列的元素个数：";
    cin >> n;
    cout << "请输入元素：";
    for (int i = 0; i < n; ++i) {
        cin >> elem;
        queue.push(elem);
    }
    queue.display();
}

void test1() {
    queue<int> queue;
    cout << "请输入要保存进队列的元素个数：";
    int n;
    cin >> n;
    cout << "请输入元素：";
    for (int i = 0; i < n; ++i) {
        int elem;
        cin >> elem;
        queue.push(elem);
    }
    reverse(queue);
    cout << "转置后：";
    while (!queue.empty()) {
        cout << queue.front() << " ";
        queue.pop();
    }
}

void reverse(queue<int> &queue) {
    stack<int> stack;
    while (!queue.empty()) {
        stack.push(queue.front());
        queue.pop();
    }
    while (!stack.empty()) {
        queue.push(stack.top());
        stack.pop();
    }
}
