#include <gtest/gtest.h>
#include "Shpyrka_queue.cpp"

TEST(QueueTests, pushStringTest) {
    Queue<string> q;
    q.push(1, "apple", 3);
    q.push(2, "banana", 3);
    q.push(3, "mango", 1);
    q.push(4, "papaya", 3);

    ASSERT_EQ("apple", q.pop());
    ASSERT_EQ("banana", q.pop());
    ASSERT_EQ("papaya", q.pop());
    ASSERT_EQ("mango", q.pop());
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTests, pushIntTest) {
    Queue<int> q;
    q.push(1, 1, 3);
    q.push(2, 2, 3);
    q.push(3, 3, 1);
    q.push(4, 4, 3);

    ASSERT_EQ(1, q.pop());
    ASSERT_EQ(2, q.pop());
    ASSERT_EQ(4, q.pop());
    ASSERT_EQ(3, q.pop());
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTests, frontTest) {

}

TEST(QueueTests, backTest) {
    
}

TEST(QueueTests, sizeTest) {
    
}

TEST(QueueTests, emptyTest) {
    
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}