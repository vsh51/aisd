#include <iostream>
#include <bitset>
using namespace std;

class Set {
private:
    using BYTE = unsigned int;
    
    BYTE container;
    int hv = 15;
    int lv = 0;

    bool valid(size_t data) const {
        return data >= lv && data <= hv;
    };

public:
    Set() : container(BYTE()) {};
    Set(BYTE b) : container(b) {};

    void insert(size_t data) {
        if (!valid(data)) throw out_of_range("data is not valid");
        container |= (1 << data - 1);
    };

    void pop(size_t data) {
        if (!valid(data)) throw out_of_range("data is not valid");
        container &= ~(1 << data - 1);
    }

    bool contain(size_t data) const {
        if (!valid(data)) throw out_of_range("data is not valid");

        BYTE tmp = 1;
        tmp <<= data - 1;
        tmp &= container;

        return tmp;
    };

    Set& operator=(const Set& other) {
        if (this == &other) {
            return *this;
        }
        else {
            this->container = other.container;
        }
        return *this;
    }

    Set operator&(const Set& other) const {
        BYTE tmp = this->container | other.container;
        return Set(tmp);
    };

    Set operator%(const Set& other) const {
        BYTE tmp = this->container & other.container;
        return Set(tmp);
    };

    Set operator/(const Set& other) const {
        BYTE tmp = ~other.container;
        BYTE res = this->container & tmp;
        return Set(res);
    };

    friend ostream& operator<<(ostream& os, const Set& S) {
        bool checker = false;
        os << "[ ";
        for (int i = 0; i < S.hv; ++i) {
            if (S.contain(i)) {
                checker = true;
                os << i << ", ";
            };
        }
        if (checker) os << "\b\b ]" << endl;
        else os << "\b\b \b" << endl;
        return os;
    }
};