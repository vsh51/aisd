#include <gtest/gtest.h>
#include "Shpyrka_queue.cpp"

TEST(QueueTests, addTest) {
    Queue<string> q;
    q.add(1, "apple", 3);
    q.add(2, "banana", 3);
    q.add(3, "mango", 1);
    q.add(4, "papaya", 3);

    ASSERT_EQ("apple", q.pop());
    ASSERT_EQ("banana", q.pop());
    ASSERT_EQ("papaya", q.pop());
    ASSERT_EQ("mango", q.pop());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}