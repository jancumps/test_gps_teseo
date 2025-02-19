#include <gtest/gtest.h>

import test_module;

class TestClassTest : public testing::Test {
protected:
    TestClassTest() {}
   
    // ~TestClassTest() override = default;
    test_module::TestClass o;
};


TEST(string_view, match) {
    test_module::TestClass o;
    EXPECT_TRUE(o.match("match")); // should pass
}

TEST(string_view, missmatch) {
    test_module::TestClass o;
    EXPECT_FALSE(o.match("mismatch")); // should pass
}

TEST_F(TestClassTest, match) {
    EXPECT_TRUE(o.match("match")); // should pass
}