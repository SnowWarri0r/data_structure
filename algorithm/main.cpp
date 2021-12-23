#include <iostream>
#include <queue>
#include <stack>

using namespace std;

void reverse(queue<int> &queue);

void test1();

int main() {
    test1();
    return 0;
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
