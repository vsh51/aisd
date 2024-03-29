#include <gtest/gtest.h>
#include <sstream>
#include "Shpyrka_queue.cpp"

// //////////////////////// //
// TESTS FOR PRIORITY QUEUE //
// //////////////////////// //
TEST(PriorityQueueTests, pushStringTest) {
    PriorityQueue<string> q;
    q.push("apple", 3);
    q.push("banana", 3);
    q.push("mango", 1);
    q.push("papaya", 3);
    ASSERT_EQ("apple", q.pop());
    ASSERT_EQ("banana", q.pop());
    ASSERT_EQ("papaya", q.pop());
    ASSERT_EQ("mango", q.pop());
    EXPECT_TRUE(q.isEmpty());
}

TEST(PriorityQueueTests, pushIntTest) {
    PriorityQueue<int> q;
    q.push(1, 3);
    q.push(2, 3);
    q.push(3, 1);
    q.push(4, 3);

    ASSERT_EQ(1, q.pop());
    ASSERT_EQ(2, q.pop());
    ASSERT_EQ(4, q.pop());
    ASSERT_EQ(3, q.pop());
    EXPECT_TRUE(q.isEmpty());
}

TEST(PriorityQueueTests, frontTest) {
    PriorityQueue<int> q;

    q.push(1, 3);
    EXPECT_EQ(1, q.front());

    q.push(2, 3);
    EXPECT_EQ(1, q.front());

    q.push(3, 4);
    EXPECT_EQ(3, q.front());

    q.push(4, 4);
    EXPECT_EQ(3, q.front());
    
    q.push(5, 3);
    EXPECT_EQ(3, q.front());
}

TEST(PriorityQueueTests, backTest) {
    PriorityQueue<int> q;

    q.push(1, 3);
    EXPECT_EQ(1, q.back());

    q.push(2, 3);
    EXPECT_EQ(2, q.back());

    q.push(3, 4);
    EXPECT_EQ(2, q.back());

    q.push(4, 4);
    EXPECT_EQ(2, q.back());
    
    q.push(5, 3);
    EXPECT_EQ(5, q.back());
}

TEST(PriorityQueueTests, sizeTest) {
    PriorityQueue<int> q;

    q.push(1, 3);
    EXPECT_EQ(1, q.size());

    q.push(2, 3);
    EXPECT_EQ(2, q.size());

    q.push(3, 4);
    EXPECT_EQ(3, q.size());

    q.pop();
    EXPECT_EQ(2, q.size());
}

TEST(PriorityQueueTests, emptyTest) {
    PriorityQueue<string> q;
    EXPECT_TRUE(q.isEmpty());
    
    q.push("apple", 3);
    EXPECT_FALSE(q.isEmpty());

    q.pop();
    EXPECT_TRUE(q.isEmpty());
}

TEST(PriorityQueueTests, printTest) {
    PriorityQueue<string> q;
    q.push("apple", 3);
    q.push("banana", 3);
    q.push("mango", 1);
    q.push("papaya", 3);

    ostringstream os;
    q.print(os);

    ASSERT_EQ(os.str(), "apple banana papaya mango \n");
}

// /////////////// //
// TESTS FOR QUEUE //
// /////////////// //
TEST(QueueTests, pushStringTest) {
    Queue<string> q;
    q.push("apple");
    q.push("banana");
    q.push("mango");
    q.push("papaya");
    ASSERT_EQ("apple", q.pop());
    ASSERT_EQ("banana", q.pop());
    ASSERT_EQ("mango", q.pop());
    ASSERT_EQ("papaya", q.pop());
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTests, pushIntTest) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    ASSERT_EQ(1, q.pop());
    ASSERT_EQ(2, q.pop());
    ASSERT_EQ(3, q.pop());
    ASSERT_EQ(4, q.pop());
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTests, frontTest) {
    Queue<int> q;

    q.push(1);
    EXPECT_EQ(1, q.front());

    q.push(2);
    EXPECT_EQ(1, q.front());
}

TEST(QueueTests, backTest) {
    Queue<int> q;

    q.push(1);
    EXPECT_EQ(1, q.back());

    q.push(2);
    EXPECT_EQ(2, q.back());
}

TEST(QueueTests, sizeTest) {
    Queue<int> q;

    q.push(1);
    EXPECT_EQ(1, q.size());

    q.push(2);
    EXPECT_EQ(2, q.size());

    q.push(3);
    EXPECT_EQ(3, q.size());

    q.pop();
    EXPECT_EQ(2, q.size());
}

TEST(QueueTests, emptyTest) {
    Queue<string> q;
    EXPECT_TRUE(q.isEmpty());
    
    q.push("apple");
    EXPECT_FALSE(q.isEmpty());

    q.pop();
    EXPECT_TRUE(q.isEmpty());
}

TEST(QueueTests, printTest) {
    Queue<string> q;
    q.push("apple");
    q.push("banana");
    q.push("mango");
    q.push("papaya");

    ostringstream os;
    q.print(os);

    ASSERT_EQ(os.str(), "apple banana mango papaya \n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}