#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "hashtable.cpp"
using namespace std;

TEST(TableTests, putTest) {
    HashTable hs;

    try {
        hs.has_own_property("c1");
    } catch (const HashTable::key_not_found& err) {
        ASSERT_EQ(err.what(), "key is not found");
    }

    hs.put("c1", "poland").put("c2", "china");

    ASSERT_EQ(hs.has_own_property("c1"), 1);
    ASSERT_EQ(hs.has_own_property("c2"), 1);
}

TEST(TableTests, getValueTest) {
    HashTable hs;

    try {
        hs.get_value("c1");
    } catch (const HashTable::key_not_found& err) {
        ASSERT_EQ(err.what(), "key is not found");
    }

    hs.put("c1", "poland").put("c2", "china");
    ASSERT_EQ(hs.get_value("c1"), "poland");
    ASSERT_EQ(hs.get_value("c2"), "china");
}

TEST(TableTests, removeTest) {
    HashTable hs;

    try {
        hs.remove("c1");
    } catch (const HashTable::key_not_found& err) {
        ASSERT_EQ(err.what(), "key is not found");
    }

    hs.put("c1", "poland").put("c2", "china");
    ASSERT_EQ(hs.get_value("c1"), "poland");
    
    hs.remove("c1").remove("c2");
    try {
        hs.remove("c1");
    } catch (const HashTable::key_not_found& err) {
        ASSERT_EQ(err.what(), "key is not found");
    }
    
    try {
        hs.remove("c2");
    } catch (const HashTable::key_not_found& err) {
        ASSERT_EQ(err.what(), "key is not found");
    }
}

TEST(TableTests, hasOwnPropTest) {
    HashTable hs;

    try {
        hs.has_own_property("c1");
    } catch (const HashTable::key_not_found& err) {
        ASSERT_EQ(err.what(), "key is not found");
    }

    hs.put("c1", "poland");
    EXPECT_TRUE(hs.has_own_property("c1"));
}

TEST(TableTests, getAmountOfRecordsTest) {
    HashTable hs;
    EXPECT_EQ(hs.get_amount_of_records(), 0);

    hs.put("c2", "china");
    EXPECT_EQ(hs.get_amount_of_records(), 1);

    hs.put("c1", "poland");
    EXPECT_EQ(hs.get_amount_of_records(), 2);

    hs.remove("c1");
    EXPECT_EQ(hs.get_amount_of_records(), 1);

    hs.remove("c2");
    EXPECT_EQ(hs.get_amount_of_records(), 0);
}

TEST(TableTests, printTest) {
    HashTable hs;
    string checker = "c2\t|\tchina\nc1\t|\tpoland\n"; 
    ostringstream ss;

    hs.put("c1", "poland").put("c2", "china");
    hs.print(ss);

    ASSERT_EQ(ss.str(), checker);
}

TEST(TableTests, constructorTest) {
    try {
        HashTable hs(-1);
    } catch (const exception& err) {
        EXPECT_TRUE(err.what());
    }

    try {
        HashTable hs(1);
    } catch (const invalid_argument& err) {
        string errw = err.what();
        ASSERT_EQ(errw, "size must be grater than 1");
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}