#include <iostream>
#include "AVL.cpp"
using namespace std;

int main() {
    AVL_tree<int> T;
    T.insert(1);
    T.insert(2);
    T.insert(3);
    T.insert(5);
    T.printOn(cout);
    return 0;
}