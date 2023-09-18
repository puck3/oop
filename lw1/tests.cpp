#include <iostream>
#include <gtest/gtest.h>

TEST(test_add_figure, basic_test_set) {
    testing::internal::CaptureStdout();
    std::cout << "Hello world";
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output == "Hello world");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}