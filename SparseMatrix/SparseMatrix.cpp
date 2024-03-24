#include <iostream>
using namespace std;

template <typename data>
class SparseMatrix {
private:
    using index = unsigned int;
    struct column {
        index col;
        data useful_data;
        column* next;

        column(index col = 0, data useful_data = data(), column* next = nullptr) :
            col(col), useful_data(useful_data), next(next) {};

        ~column() {
            delete next;
        }
    };

    struct row {
        index rw;
        column* columns;
        row* next;

        row(index rw = 0, column* columns = nullptr, row* next = nullptr):
            rw(rw), columns(columns), next(next) {};

        ~row() {
            delete next;
        }
    };

    row* head;
    index amount_of_records;

public:

    SparseMatrix() {
        head = new row(0);
        amount_of_records = 0;
    }

    bool is_empty(index rw, index col) {
        row* tmpptr = head;
        while (tmpptr != nullptr) {
            if (tmpptr->rw == rw) {
                column* tmpptr2 = tmpptr->columns;
                while (tmpptr2 != nullptr) {
                    if (tmpptr2->col == col) {
                        return false;
                    }
                    tmpptr2 = tmpptr2->next;
                }
            }
            tmpptr = tmpptr->next;
        }
        return true;
    }

    SparseMatrix& add(index rw, index col, data dt) {
        row* tmpptr = head;
        while (tmpptr->next != nullptr && tmpptr->next->rw < rw) {
            tmpptr = tmpptr->next;
        }

        if (tmpptr->next != nullptr) {
            if (tmpptr->next->rw == rw) {
                tmpptr = tmpptr->next;
                column* tmpptr2 = tmpptr->columns;

                while (tmpptr2->next != nullptr && tmpptr2->next->col < col) {
                    tmpptr2 = tmpptr2->next;
                }

                if (tmpptr2->next != nullptr) {
                    if (tmpptr2->next->col == col) {
                        throw "trying to add to existing index";
                    }
                }
                else if (tmpptr2->next == nullptr && tmpptr2->col == col) {
                    throw "trying to add to existing index";
                }
                else {
                    column* new_column = new column(col, dt, tmpptr2->next);
                    tmpptr2->next = new_column;
                }
            }
        }
        else {
            row* new_row = new row(rw, new column(col, dt), tmpptr->next);
            tmpptr->next = new_row;
        }
        ++amount_of_records;
        return *this;
    }

    data read(index rw, index col) {
        if (!is_empty(rw, col)) {
            row* tmpptr = head;
            while (tmpptr->rw != rw) tmpptr = tmpptr->next;

            column* tmpptr2 = tmpptr->columns;
            while (tmpptr2->col != col) tmpptr2 = tmpptr2->next;

            return tmpptr2->useful_data;
        }
        else {
            return data();
        }
    }

    bool del(index rw, index col) {
        if (!is_empty(rw, col)) {
            row* tmpptr = head;
            while (tmpptr->rw != rw) tmpptr = tmpptr->next;

            column* tmpptr2 = tmpptr->columns;
            while (tmpptr2->next != nullptr && tmpptr2->next->col != col) tmpptr2 = tmpptr2->next;

            if (tmpptr2->next == nullptr) {
                if (tmpptr2 == tmpptr->columns) {
                    delete tmpptr2;
                    tmpptr->columns = nullptr;
                }
                else {
                    delete tmpptr2;
                }
            }
            else {
                column* trashcan = tmpptr2->next;
                tmpptr2->next = tmpptr2->next->next;
                delete trashcan;
            }
            --amount_of_records;
            return 1;
        }
        else {
            return 0;
        }
    }

    void fix_empty_rows() {
        row* tmpptr = head;
        row* trashcan;
        while (tmpptr->next != nullptr) {
            if (tmpptr->next->columns == nullptr && tmpptr != head) {
                trashcan = tmpptr->next;
                tmpptr->next = tmpptr->next->next;
                delete trashcan;
            }
            tmpptr = tmpptr->next;
        }
        if (tmpptr != head && tmpptr->columns == nullptr) {
            row* nearly_last = head;
            while (nearly_last->next->next != nullptr) nearly_last = nearly_last->next;
            
            trashcan = nearly_last->next;
            nearly_last->next = nearly_last->next->next;
            delete trashcan;
        }
    }

    index get_amount_of_records() const { return amount_of_records; };
};