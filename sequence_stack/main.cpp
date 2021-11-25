#include "SequenceStack.h"
#include <iomanip>

void test0();

void Dto16(unsigned int m);

void postfix(const std::string &e, std::string &f);

int priority(char c);

void sort();

void test3();

double evalpost(const std::string &f);

int main() {
//    test0();
//    Dto16(256);
//    sort();
    test3();
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

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    else return 3;
}

void postfix(const std::string &e, std::string &f) {
    SequenceStack<char> stack;
    for (char c: e) {
        if ('0' <= c && c <= '9') {
            f += c;
        } else {
            if (stack.empty() || c == '(') {
                stack.push(c);
            } else {
                if (c == ')') {
                    while (stack.top() != '(') {
                        f += stack.top();
                        stack.pop();
                    }
                    stack.pop();
                } else {
                    while (!stack.empty() && priority(stack.top()) >= priority(c)) {
                        f += stack.top();
                        stack.pop();
                    }
                    stack.push(c);
                }
            }
        }
    }
    while (!stack.empty()) {
        f += stack.top();
        stack.pop();
    }
}

double evalpost(const std::string &f) {
    SequenceStack<double> stack;
    double leftOperator, rightOperator;
    for (char c: f) {
        if ('0' <= c && c <= '9') stack.push(c - '0');
        else {
            rightOperator = stack.top();
            stack.pop();
            leftOperator = stack.top();
            stack.pop();
            switch (c) {
                case '+': {
                    stack.push(leftOperator + rightOperator);
                    break;
                }
                case '-': {
                    stack.push(leftOperator - rightOperator);
                    break;
                }
                case '*' : {
                    stack.push(leftOperator * rightOperator);
                    break;
                }
                case '/': {
                    stack.push(leftOperator / rightOperator);
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
    double ans = stack.top();
    stack.pop();
    return ans;
}

void test3() {
    std::string ans;
    std::string input;
    std::cout << "请输入中缀表达式：";
    std::cin >> input;
    postfix(input, ans);
    std::cout << "后缀表达式：" << ans << std::endl;
    std::cout << "计算结果：" << std::fixed << std::setprecision(2) << evalpost(ans);
}