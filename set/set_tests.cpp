#include <gtest/gtest.h>
#include "Shpyrka_set.cpp"
using namespace std;

const int HV = 16;

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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};