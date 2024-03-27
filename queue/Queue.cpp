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
            while (tmpptr != nullptr && tmpptr->priority >= priority) {
                tmpptr = tmpptr->next;
            }

            if (tmpptr == head) {
                node* nn = new node(priority, data, id, nullptr, head);
                head->prev = nn;
                head = nn;
            }
            else if (tmpptr == nullptr) {
                node* nn = new node(priority, data, id, tail, nullptr);
                tail->next = nn;
                tail = nn;
            }
            // process base case
        }
    };

    datatype pop() {
        datatype rt = tail->prev->prev->prev->data;

        return rt;
    };
};

int main () {
    Queue<int> q;
    q.add(3, 2, 2);
    q.add(3, 1, 2);
    q.add(1, 25, 3);    
    q.add(2, 47, 4);
    cout << q.pop();
};