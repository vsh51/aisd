#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <typename data_t>
class Stack {
private:
    struct Node {
        data_t data;
        Node* next;

        Node(data_t data, Node* next = nullptr) : data(data), next(next) {};
    };
    Node* top;

public:
    Stack() : top(nullptr) {};

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

class fix_converter {
protected:
    const string priorities[3]{ "#()", "+-", "*/" };

    Stack<char> op_stack;
    
    string input_string;
    string resulting_string = "";
    
    int getPrior(char op) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (op == priorities[i][j]) return i;
            }
        }
        if (op == priorities[0][2]) return 0;

        return -1;
    }

    bool isOperand(char op) { return getPrior(op) == -1; };
    bool isOperator(char op) { return !isOperand(op); };

public:

    fix_converter(string input_string) : input_string(input_string) {};

    string get_rpn() {
        if (isOperator(input_string[input_string.length() - 2])) {
            resulting_string = input_string;
            return resulting_string;
        }

        for (int i = 0; i < input_string.length(); ++i) {
            if (input_string[i] == '.') {
                while (!op_stack.isEmpty()) {
                    resulting_string += op_stack.pop();
                }
                resulting_string += '.';
            }
            else if (isOperand(input_string[i])) {
                resulting_string += input_string[i];
            }
            else if (input_string[i] == '(') {
                op_stack.push(input_string[i]);
            }
            else if (input_string[i] == ')') {
                char popped;
                do {
                    popped = op_stack.pop();
                    resulting_string += popped;
                } while (popped != '(');
                resulting_string.pop_back();
            }
            else if (isOperator(input_string[i])) {
                try {
                    char operation = op_stack.pop();
                    while (getPrior(input_string[i]) <= getPrior(operation)) {
                        resulting_string += operation;
                        operation = op_stack.pop();
                    }
                    op_stack.push(operation);
                    op_stack.push(input_string[i]);
                }
                catch (...) {
                    op_stack.push(input_string[i]);
                }
            }
        }
        return resulting_string;
    }
};

class rpnCounter : private fix_converter {
private:
    Stack<double> symbols_stack;

    double perform_operation(double operand2, char operation, double operand1) {
        switch (operation) {
            case '+':
                return operand2 + operand1;
            case '-':
                return operand2 - operand1;
            case '/':
                if (!isinf(operand2 / operand1)) {
                    return operand2 / operand1;
                }
                else {
                    throw "division by zerro error";
                }
            case '*':
                return operand2 * operand1;
            default:
                break;
        }
        return 0;
    }

public:
    rpnCounter(string input_string) : fix_converter(input_string) { get_rpn(); };

    string get_rpn() {
        return fix_converter::get_rpn();
    }

    double count() {
        for (int i = 0; i < resulting_string.length() - 1; ++i) {
            if (!isOperator(resulting_string[i])) {
                // neyavne peretvorennia char v double: char - '0'
                symbols_stack.push(resulting_string[i] - '0');
            }
            else {
                double res = perform_operation(symbols_stack.pop(), resulting_string[i], symbols_stack.pop());
                symbols_stack.push(res);
            }
        }
        return symbols_stack.pop();
    }

};