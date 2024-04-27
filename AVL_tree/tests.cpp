#include <gtest/gtest.h>
#include <iostream>
#include "AVL.cpp"
using namespace std;

TEST(AVL, empty) {
    AVL_tree<char> T;
    EXPECT_EQ(0, T.count('a'));
    EXPECT_EQ(0, T.delete_key('a'));
    
    ostringstream os;
    T.printOn(os);
    ASSERT_EQ(os.str(), "\n");
}

TEST(AVL, insert_1_test) {
    AVL_tree<char> T;
    T.insert('a');
    
    ostringstream os;
    T.printOn(os);
    ASSERT_EQ(os.str(), "a:1\n");
}

TEST(AVL, insert_2_test) {
    AVL_tree<char> T;
    T.insert('a');
    T.insert('b');
    
    ostringstream os;
    T.printOn(os);
    ASSERT_EQ(os.str(), "     b:1\na:1\n");
}

TEST(AVL, insert_3_test) {
    AVL_tree<char> T;
    T.insert('a');
    T.insert('b');
    T.insert('c');

    ostringstream os;
    T.printOn(os);
    ASSERT_EQ(os.str(), "     c:1\nb:1\n     a:1\n");
}

TEST(AVL, count_test) {
    AVL_tree<char> T;
    T.insert('a');
    EXPECT_EQ(1, T.count('a'));
    T.insert('a');
    EXPECT_EQ(2, T.count('a'));
    T.insert('a');
    T.delete_key('a');
    EXPECT_EQ(2, T.count('a'));
    
    T.set_count('a', 100);
    T.delete_key('a');
    EXPECT_EQ(99, T.count('a'));
}

TEST(AVL, insert_and_pint_test1) {
    AVL_tree<char> T;
    T.insert('a');
    T.insert('b');
    T.insert('c');
    T.insert('d');
    T.insert('e');
    T.insert('f');
    T.insert('b');
    T.insert('g');

    ostringstream os;
    T.printOn(os);

    ASSERT_EQ("          g:1\n     f:1\n          e:1\nd:1\n          c:1\n     b:2\n          a:1\n", os.str());
}

TEST(AVL, insert_and_pint_test2) {
    AVL_tree<int> T;
    T.insert(1);
    T.insert(2);
    T.insert(3);
    T.insert(4);
    T.insert(5);
    T.insert(4);

    ostringstream os;
    T.printOn(os);

    ASSERT_EQ("          5:1\n     4:2\n          3:1\n2:1\n     1:1\n", os.str());
}

TEST(AVL, delete_test) {
    AVL_tree<int> T;
    T.insert(1);
    T.insert(2);
    T.insert(3);
    T.insert(4);
    T.insert(5);
    T.insert(4);

    ostringstream os;
    T.printOn(os);
    ASSERT_EQ("          5:1\n     4:2\n          3:1\n2:1\n     1:1\n", os.str());

    os.str("");
    T.delete_key(4);
    T.printOn(os);
    ASSERT_EQ("          5:1\n     4:1\n          3:1\n2:1\n     1:1\n", os.str());

    os.str("");
    T.delete_key(4);
    T.printOn(os);
    ASSERT_EQ("          5:1\n     3:1\n2:1\n     1:1\n", os.str());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}