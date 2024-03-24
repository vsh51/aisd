#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
using namespace std;

using data_t = int;

class IntStack {
private:
    struct Node {
        data_t data;
        Node* next;

        Node(data_t data, Node* next=nullptr) : data(data), next(next) {};
    };
    Node* top;

public:
    IntStack() : top(nullptr) {};

    bool isEmpty() {
        return top == nullptr;
    }

    void push(data_t data) {
        Node* new_node = new Node(data, top);
        top = new_node;
    }

    data_t pop() {
        Node* tmpptr = top;
        data_t val;
        if (!this->isEmpty()) {
            val = tmpptr->data;
            top = top->next;
            delete tmpptr;
            return val;
        }
        else {
            throw out_of_range("Trying to pop from empty stack");
        }
    }

    void print(ostream& os) {
        Node* ptr = top;

        while (ptr != nullptr) {
            os << ptr->data << " ";   
            ptr = ptr->next;
        }

        delete ptr;
        os << endl;
    }
};

TEST(StackTests, isEmpty) {
    IntStack* stack = new IntStack;
    ASSERT_TRUE(stack->isEmpty());
    stack->push(5);
    ASSERT_FALSE(stack->isEmpty());
}

TEST(StackTests, push2empty) {
    IntStack* stack = new IntStack;
    ASSERT_TRUE(stack->isEmpty());
    
    stack->push(5);
    ASSERT_DOUBLE_EQ(stack->pop(), 5);
}

TEST(StackTests, push2full) {
    IntStack* stack = new IntStack;
    ASSERT_TRUE(stack->isEmpty());
    
    stack->push(5);
    ASSERT_DOUBLE_EQ(stack->pop(), 5);

    stack->push(24);
    ASSERT_DOUBLE_EQ(stack->pop(), 24);
}

TEST(StackFullTest, printTest) {
    IntStack* stack = new IntStack;
    stringstream ss;
    string checker = "1 2 3 5 \n";
    stack->push(5); stack->push(3); stack->push(2); stack->push(1);
    stack->print(ss);

    ASSERT_TRUE(ss.str() == checker);
}

TEST(StackFullTest, printAfterPop) {
    IntStack* stack = new IntStack;
    stringstream ss;
    string checker = "2 3 5 \n";
    stack->push(5); stack->push(3); stack->push(2); stack->push(1);
    stack->pop();
    stack->print(ss);
    ASSERT_TRUE(ss.str() == checker);
}

TEST(StackFullTest, printEmpty) {
    IntStack* stack = new IntStack;
    stringstream ss;
    string checker = "\n";
    stack->print(ss);
    ASSERT_TRUE(ss.str() == checker);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}