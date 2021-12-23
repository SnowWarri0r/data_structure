#include "QueueSimulator.h"

using namespace std;

int main() {
    QueueSimulator<int> queue;
    cout << "请输入入队元素数量：";
    int n;
    cin >> n;
    cout << "请输入入队元素：";
    for (int i = 0; i < n; ++i) {
        int elem;
        cin >> elem;
        queue.enqueue(elem);
    }
    queue.display();
    cout << "请输入出队列数量：";
    cin >> n;
    int elem;
    for (int i = 0; i < n && !queue.empty(); ++i) {
        queue.dequeue(elem);
    }
    queue.display();
    cout << "请输入入队元素数量：";
    cin >> n;
    cout << "请输入入队元素：";
    for (int i = 0; i < n; ++i) {
        cin >> elem;
        queue.enqueue(elem);
    }
    queue.display();
    return 0;
}
