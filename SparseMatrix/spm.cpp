#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "SparseMatrix.cpp"

TEST(GeneralTests, amountOfRecords) {
    SparseMatrix<int> spm;
    EXPECT_EQ(spm.get_amount_of_records(), 0);
    spm.add(1, 1, 1);
    EXPECT_EQ(spm.get_amount_of_records(), 1);
}

TEST(GeneralTests, amountOfRecordsDelete) {
    SparseMatrix<int> spm;
    EXPECT_EQ(spm.get_amount_of_records(), 0);
    spm.add(1, 1, 1);
    EXPECT_EQ(spm.get_amount_of_records(), 1);
    spm.del(1, 1);
    EXPECT_EQ(spm.get_amount_of_records(), 0);
}

TEST(GeneralTests, DeleteVoid) {
    SparseMatrix<int> spm;
    EXPECT_EQ(0, spm.del(1, 1));
}

TEST(GeneralTests, readVoid) {
    SparseMatrix<int> spm;
    EXPECT_EQ(int(), spm.read(1, 1));

    SparseMatrix<double> spm1;
    EXPECT_EQ(double(), spm1.read(1, 1));
}

TEST(GeneralTests, add2void) {
    SparseMatrix<int> spm;
    spm.add(1, 1, 8);
    EXPECT_EQ(8, spm.read(1, 1));
}

TEST(GeneralTests, add2existing) {
    SparseMatrix<int> spm;
    spm.add(1, 1, 8);
    
    bool checker = 0;
    try {
        spm.add(1, 1, 24);
    }
    catch (...) {
        checker = 1;
    }
    EXPECT_TRUE(checker);
}

TEST(GeneralTests, isEmpty) {
    SparseMatrix<int> spm;
    EXPECT_TRUE(spm.is_empty(1, 1));
    spm.add(1, 1, 8);
    EXPECT_FALSE(spm.is_empty(1, 1));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}