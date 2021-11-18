#include "SequenceStack.h"

void test0();

void Dto16(unsigned int m);

void sort();

int main() {
//    test0();
//    Dto16(256);
    sort();
    return 0;
}

void test0() {
    SequenceStack<int> stack;
    std::cout << "请输入要放入栈多少个值：";
    int n;
    std::cin >> n;
    std::cout << "请输入要放入栈中的值：";
    int data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        stack.push(data);
    }
    stack.display();
}

void sort() {
    SequenceStack<int> stack1, stack2;
    std::cout << "请输入要放入栈多少个值：";
    int n;
    std::cin >> n;
    std::cout << "请输入要放入栈中的值：";
    int data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        if (stack1.empty() || data > stack1.top())
            stack1.push(data);
        else {
            while (stack1.top() > data) {
                stack2.push(stack1.top());
                stack1.pop();
            }
            stack1.push(data);
            while (!stack2.empty()) {
                stack1.push(stack2.top());
                stack2.pop();
            }
        }
    }
    stack1.display();
}

void Dto16(unsigned int m) {
    std::string s = "0123456789ABCDEF";
    SequenceStack<char> stack;
    while (m != 0) {
        unsigned int u = m % 16;
        stack.push(s[u]);
        m /= 16;
    }
    std::string ans = "0x";
    while (!stack.empty()) {
        ans += stack.top();
        stack.pop();
    }
    std::cout << ans << std::endl;
}

void postfix(std::string &e, std::string &f) {

}