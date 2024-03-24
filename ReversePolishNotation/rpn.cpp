#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "ReversePolishNotation.cpp"
using namespace std;

TEST(fix_converter, infix2postfix) {
    fix_converter fx("a+(b-c)/k.");
    EXPECT_EQ("abc-k/+.", fx.get_rpn());
}

TEST(fix_converter, postfix2postfix) {
    fix_converter fx("abc-k/+.");
    EXPECT_EQ("abc-k/+.", fx.get_rpn());
}

TEST(fix_converter, infix2postfixNumbers) {
    fix_converter fx("2+(3-1)/8.");
    EXPECT_EQ("231-8/+.", fx.get_rpn());
}

TEST(fix_converter, postfix2postfixNumbers) {
    fix_converter fx("231-8/+.");
    EXPECT_EQ("231-8/+.", fx.get_rpn());
}

TEST(rpnCounter, divisionByZerro) {
    bool checker = 0;
    rpnCounter rpnc("2+(3-1)/0.");
    try {
        rpnc.count();
    }
    catch (...) {
        checker = 1;
    }
    EXPECT_TRUE(checker);
}

TEST(rpnCounter, calc1) {
    rpnCounter rpnc("24*8+.");
    EXPECT_EQ(16, rpnc.count());
}

TEST(rpnCounter, calc2) {
    rpnCounter rpnc("248+*.");
    EXPECT_EQ(24, rpnc.count());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}