#include <gtest/gtest.h>
#include <sstream>
#include "table.cpp"

TEST(TableTests, resizeTest) {
    Table tb(1);
    tb.put("car1", "bmw");
    ASSERT_EQ(tb.get_amount_of_records(), 1);
    tb.put("car2", "lada");
    ASSERT_EQ(tb.get_amount_of_records(), 2);
};

TEST(TableTests, deleteTest) {
    Table tb(1);
    tb.put("car1", "bmw");
    ASSERT_EQ(tb.get_amount_of_records(), 1);
    tb.put("car2", "lada");
    ASSERT_EQ(tb.get_amount_of_records(), 2);
    tb.remove("car1");
    ASSERT_EQ(tb.get_amount_of_records(), 1);

    try {
        tb.has_own_property("car1");
    }
    catch (const Table::key_not_found& err) {
        ASSERT_EQ("There is no key in keys collection", err.what());
    };
};

TEST(TableTests, getValueTest) {
    Table tb(1);
    tb.put("car1", "bmw");
    tb.put("car2", "lada");
    tb.remove("car1");

    try {
        tb.get_value("car1");
    }
    catch (const Table::key_not_found& err) {
        ASSERT_EQ("There is no key in keys collection", err.what());
    };

    try {
        string k = tb["car1"];
    }
    catch (const Table::key_not_found& err) {
        ASSERT_EQ("There is no key in keys collection", err.what());
    };

    ASSERT_EQ(tb["car2"], "lada");
}

TEST(TableTests, printTest) {
    Table tb(1);
    stringstream ss;
    tb.put("car1", "bmw");
    tb.put("car2", "lada");

    tb.print(ss);
    ASSERT_EQ(ss.str(), "car1: bmw\ncar2: lada\n");
    ss.str("");

    tb.put("car2", "toyota");
    tb.print(ss);
    ASSERT_EQ(ss.str(), "car1: bmw\ncar2: toyota\n");
    ss.str("");

    tb.remove("car1");
    tb.print(ss);
    ASSERT_EQ(ss.str(), "car2: toyota\n");
    ss.str("");
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}