#include <iostream>
#include <queue>
using namespace std;

template <typename datatype>
class PriorityQueue {
protected:
    struct node {
        datatype data;
        int priority;
        node* prev;
        node* next;

        node(int priority = 0, datatype data = datatype(), node* prev = nullptr, node* next = nullptr):
            priority(priority), data(data), prev(prev), next(next) {};
    };

    node* head;
    node* tail;
    unsigned int amount_of_items;

public:
    class is_empty_error : public logic_error {
        public:
            is_empty_error(const char* mess = "the queue is empty") : logic_error(mess) {};
    };

public:
    PriorityQueue() {
        this->head = nullptr;
        this->tail = nullptr;
        amount_of_items = 0;
    };

    bool isEmpty() {
        return head == nullptr;
    };

    virtual void push(datatype data, int priority = 0) {
        if (isEmpty()) {
            head = new node(priority, data, nullptr, nullptr);
            tail = head;
        }
        else {
            node* tmpptr = head;
            while (tmpptr != nullptr && priority <= tmpptr->priority) {
                tmpptr = tmpptr->next;
            }
            if (tmpptr == head) {
                node* nn = new node(priority, data, nullptr, head);
                head->prev = nn;
                head = nn;
            }
            else if (tmpptr == nullptr) {
                node* nn = new node(priority, data, tail, nullptr);
                tail->next = nn;
                tail = nn;
            }
            else {
                node* nn = new node(priority, data, tmpptr->prev, tmpptr);
                tmpptr->prev->next = nn;
                tmpptr->prev = nn;
            }
        }
        ++amount_of_items;
    };

    datatype pop() {
        if (!isEmpty()) {
            datatype dt = head->data;
            node* traschcan = head;
            
            if (head->next != nullptr) {
                head->next->prev = nullptr;
            }
            if (head->next == nullptr) {
                tail = nullptr;
            }

            head = head->next;
            delete traschcan;
            --amount_of_items;
            
            return dt;
        }
        else {
            throw is_empty_error();
        }
    };

    datatype& front() {
        if(!isEmpty()) return head->data;
        else throw is_empty_error();
    }

    datatype& back() {
        if(!isEmpty()) return tail->data;
        else throw is_empty_error();
    }

    unsigned int size() {
        return amount_of_items;
    }

    void print(ostream& os) {
        node* tmpptr = head;
        while (tmpptr != nullptr) {
            os << tmpptr->data << " ";
            tmpptr = tmpptr->next;
        }
        os << "\n";
    }

    ~PriorityQueue() {
        node* tmpptr = head;
        while (!isEmpty()) {
            pop();
        }
    }
};

template <typename datatype>
class Queue : public PriorityQueue<datatype> {
public:
    virtual void push(datatype data) {
        PriorityQueue<datatype>::push(data);
    };
};