#include <iostream>
using namespace std;

template <typename datatype>
class Queue {
private:
    struct node {
        datatype data;
        int priority;
        unsigned int id;
        node* prev;
        node* next;

        node(int priority = 0, datatype data = datatype(), unsigned int id = 0, node* prev = nullptr, node* next = nullptr):
            priority(priority), data(data), id(id), prev(prev), next(next) {};
    }

    node* head;
    unsigned int amount_of_items;

};

int main () {

};