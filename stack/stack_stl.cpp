#include <gtest/gtest.h>
#include <iostream>
#include <stack>
using namespace std;

void print(stack<int> st, ostream& os)
{
    size_t size = st.size();
    for (int i = 0; i < size; ++i) {
        os << st.top() << " ";
        st.pop();
    }
    os << "\n";
}

TEST(StackSTLtests, printTest) {
	stack<int> st;
    st.push(4); st.push(8); st.push(24);
    stringstream ss;
    string checker = "24 8 4 \n";
    print(st, ss);

    ASSERT_TRUE(ss.str() == checker);
}

TEST(StackSTLtests, popTest) {
	stack<int> st;
    st.push(4); st.push(9); st.push(14); st.push(48);
    st.pop();
    stringstream ss;
    string checker = "14 9 4 \n";
    print(st, ss);

    ASSERT_TRUE(ss.str() == checker);
}

TEST(StackSTLtests, sizeTest) {
	stack<int> st;
    st.push(4); st.push(9); st.push(14); st.push(48);
    st.pop();

    ASSERT_TRUE(st.size() == 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}