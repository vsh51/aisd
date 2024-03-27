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
    };

    node* head;
    node* tail;
    unsigned int amount_of_items;

public:
    Queue() {
        this->head = nullptr;
        this->tail = nullptr;
    };

    bool isEmpty() {
        return head == nullptr;
    };

    void add(int id, datatype data, int priority = 0) {
        if (isEmpty()) {
            head = new node(priority, data, id, nullptr, nullptr);
            tail = head;
        }
        else {
            node* tmpptr = head;
            while (tmpptr->next != nullptr && tmpptr->next->priority >= priority) {
                tmpptr = tmpptr->next;
            }
            node* insert = new node(priority, data, id, tmpptr, tmpptr->next);
            if (tmpptr->next != nullptr) {
                tmpptr->next->prev = insert;
                tmpptr->next = insert;
            }
            else {
                tmpptr->next = insert;
                tail = insert;
            }
        }
    };

    datatype get() {
        datatype rt = tail->data;

        return rt;
    };
};

int main () {
    Queue<int> q;
    q.add(3, 2, 3);
    q.add(2, 47, 4);
    cout << q.get();
};