#include <gtest/gtest.h>
#include "Shpyrka_set.cpp"
#include <sstream>
using namespace std;

const int HV = 32;

TEST(Set, contain_and_insert_test) {
    Set st;
    for (int i = 0; i < HV; ++i) {
        EXPECT_FALSE(st.contain(i));
        st.insert(i);
        EXPECT_TRUE(st.contain(i));
    };
}

TEST(Set, pop_test) {
    Set st;
    for (int i = 0; i < HV; ++i) {
        EXPECT_FALSE(st.contain(i));
        st.insert(i);
        EXPECT_TRUE(st.contain(i));
        st.pop(i);
        EXPECT_FALSE(st.contain(i));
    };
}

TEST(Set, union_test) {
    Set s1;
    Set s2;

    s1.insert(3);
    s1.insert(8);

    s2.insert(15);
    s2.insert(0);

    Set s3;
    s3.insert(3);
    s3.insert(8);
    s3.insert(15);
    s3.insert(0);

    EXPECT_TRUE(s3 == (s1 & s2));
};

TEST(Set, difference_test) {
    Set s1;
    Set s2;

    s1.insert(3);
    s1.insert(8);

    s2.insert(15);
    s2.insert(3);

    Set s3;
    s3.insert(8);

    EXPECT_TRUE(s3 == (s1 / s2));
};

TEST(Set, intersection_test) {
    Set s1;
    Set s2;

    s1.insert(3);
    s1.insert(8);

    s2.insert(15);
    s2.insert(3);

    Set s3;
    s3.insert(3);

    EXPECT_TRUE(s3 == (s1 % s2));
}

TEST(Set, printTest) {
    ostringstream os;
    Set st;

    st.insert(1);
    st.insert(3);
    st.insert(13);
    os << st;
    
    ASSERT_EQ(os.str(), "[ 1, 3, 13, \b\b ]\n");

    os.str("");
    st.pop(1).pop(3).pop(13);
    os << st;

    ASSERT_EQ(os.str(), "[ \b\b \b\n");

    os.str("");
    st.insert(1);
    os << st;
    
    ASSERT_EQ(os.str(), "[ 1, \b\b ]\n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};