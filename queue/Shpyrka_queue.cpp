#include <iostream>
#include <queue>
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

    void push(int id, datatype data, int priority = 0) {
        if (isEmpty()) {
            head = new node(priority, data, id, nullptr, nullptr);
            tail = head;
        }
        
        else {
            node* tmpptr = head;
            while (tmpptr != nullptr && priority <= tmpptr->priority) {
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
            else {
                node* nn = new node(priority, data, id, tmpptr->prev, tmpptr);
                tmpptr->prev->next = nn;
                tmpptr->prev = nn;
            }
        }
        ++amount_of_items;
    };

    datatype pop() {
        datatype dt = head->data;        

        if (!isEmpty()) {
            node* traschcan = head;
            
            if (head->next != nullptr) {
                head->next->prev = nullptr;
            }
            if (head->next == nullptr) {
                tail = nullptr;
            }

            head = head->next;
            delete traschcan;
        }


        return dt;
    };

    datatype front() {
        // todo
        return datatype();
    }

    datatype back() {
        // todo
        return datatype();
    }

    unsigned int size() {
        // todo
        return int();
    }
};

// int main() {
//     Queue<string> q;
//     q.push(1, "apple", 3);
//     q.push(1, "huy", 3);
//     q.push(1, "asd", 1);

//     cout << q.pop() << "\n";
// }