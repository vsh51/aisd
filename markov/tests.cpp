#include <gtest/gtest.h>
#include "Shpyrka_markov.cpp"
#include <sstream>
using namespace std;

TEST(Markov, initTest) {
    MarkovString s("abc");
    ASSERT_EQ(s.compute(), "abc");
    ASSERT_EQ(s.get_rules_size(), 0);
};

TEST(Markov, getInitTest) {
    MarkovString s("abc");
    ASSERT_EQ(s.get_init(), "abc");
};

TEST(Markov, addRuleTest_and_getRulesSize) {
    MarkovString s("abc");
    s.add_rule("a", "b");
    s.add_rule("b", "c");
    s.add_rule("c", "d");

    ASSERT_EQ(s.get_rules_size(), 3);
};

TEST(Markov, computeTest_and_getComputedTest) {
    MarkovString s("bacaabaa");

    s.add_rule("ab", "b");
    s.add_rule("ac", "c");
    s.add_rule("aa", "a");
    
    string computed = s.compute();
    string demanded = "bcba";

    ASSERT_EQ(demanded, computed);
    ASSERT_EQ(demanded, s.get_computed());
};

TEST(Markov, showRulesTest) {
    ostringstream ist;
    MarkovString s("bacaabaa");

    s.add_rule("ab", "b");
    s.add_rule("ac", "c");
    s.add_rule("aa", "a");

    s.show_rules(ist);
    ASSERT_EQ(ist.str(), "ab -> b\nac -> c\naa -> a\n");
};

int main (int arc, char** argv) {
    ::testing::InitGoogleTest(&arc, argv);
    return RUN_ALL_TESTS();
};