#include <iostream>
#include "red_black_tree.h"

int main() {
    red_black_tree bst;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(57);

    bst.printTree();
    cout << endl
         << "After deleting" << endl;
    bst.remove(40);
    bst.remove(60);
    bst.printTree();
    return 0;
}
