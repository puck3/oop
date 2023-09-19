#include <gtest/gtest.h>
#include "vowels_count.h"

TEST(test_01, basic_tests) {
    ASSERT_TRUE(vowels_count(" ") == 0);
}

TEST(test_02, basic_tests) {
    ASSERT_TRUE(vowels_count("zxc") == 0);
}

TEST(test_03, basic_tests) {
    ASSERT_TRUE(vowels_count("queasy") == 4);
}

TEST(test_04, basic_tests) {
    ASSERT_TRUE(vowels_count("qwe asd   yui") == 5);
}

TEST(test_05, basic_tests) {
    ASSERT_TRUE(vowels_count("") == -1);
}

TEST(test_06, basic_tests) {
    ASSERT_TRUE(vowels_count("AsD") == -2);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}