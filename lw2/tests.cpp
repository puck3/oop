#include <gtest/gtest.h>
#include "twelve.hpp"


TEST(getters, basic_test) {
    std::string s = "123B";
    Twelve obj(s);
    ASSERT_EQ(obj.get_value(), s);
    ASSERT_EQ(obj.get_size(), s.size());
}

TEST(outer_funcs, converting) {
    std::string s = "0123456789AB";
    int i{0};
    for (unsigned char c : s) {
        ASSERT_EQ(twelve_to_dec(c), i);
        ASSERT_EQ(dec_to_twelve(i), c);
        ++i;
    }
}

TEST(outer_funcs, exception_handling) {
    std::string s = "qwerty";
    for (unsigned char c : s) {
        ASSERT_THROW(twelve_check(c, nullptr), std::invalid_argument);
    }
    Twelve obj;
    ASSERT_THROW(empty_check(obj), std::domain_error);
}

TEST(constructors, default_) {
    Twelve obj;
    ASSERT_EQ(obj.get_size(), 0);
    ASSERT_THROW(obj.get_value(), std::domain_error);
}

TEST(constructors, fill) {
    Twelve obj1(0);
    ASSERT_EQ(obj1.get_size(), 0);
    ASSERT_THROW(obj1.get_value(), std::domain_error);

    Twelve obj2(10, '0');
    ASSERT_EQ(obj2.get_size(), 1);
    ASSERT_EQ(obj2.get_value(), "0");

    Twelve obj3(4, '2');
    ASSERT_EQ(obj3.get_size(), 4);
    ASSERT_EQ(obj3.get_value(), "2222");

    Twelve obj4(1, 'a');
    ASSERT_EQ(obj4.get_size(), 1);
    ASSERT_EQ(obj4.get_value(), "A");

    Twelve obj5(3, 'B');
    ASSERT_EQ(obj5.get_size(), 3);
    ASSERT_EQ(obj5.get_value(), "BBB");

    ASSERT_THROW(Twelve obj6(1, 'z'), std::invalid_argument);
}

TEST(constructors, copy_string) {
    Twelve obj1("");
    ASSERT_EQ(obj1.get_size(), 0);
    ASSERT_THROW(obj1.get_value(), std::domain_error);

    Twelve obj2("132A");
    ASSERT_EQ(obj2.get_size(), 4);
    ASSERT_EQ(obj2.get_value(), "132A");

    Twelve obj3("1ab");
    ASSERT_EQ(obj3.get_size(), 3);
    ASSERT_EQ(obj3.get_value(), "1AB");

    Twelve obj4("0000");
    ASSERT_EQ(obj4.get_size(), 1);
    ASSERT_EQ(obj4.get_value(), "0");

    ASSERT_THROW(Twelve obj5("zxc"), std::invalid_argument);
}

TEST(constructors, initializer_list) {
    Twelve obj1{'1', 'A'};
    ASSERT_EQ(obj1.get_size(), 2);
    ASSERT_EQ(obj1.get_value(), "1A");

    Twelve obj2{'1', 'B', '2', 'a'};
    ASSERT_EQ(obj2.get_size(), 4);
    ASSERT_EQ(obj2.get_value(), "1B2A");

    Twelve obj3{'0', '0', '0', '0'};
    ASSERT_EQ(obj3.get_size(), 1);
    ASSERT_EQ(obj3.get_value(), "0");

    ASSERT_THROW(Twelve obj4{' '}, std::invalid_argument);
}

TEST(constructors, copy) {
    Twelve obj1{'1', 'A'};
    Twelve obj2(obj1);
    ASSERT_EQ(obj1.get_size(), obj2.get_size());
    ASSERT_EQ(obj1.get_value(), obj2.get_value());
}

TEST(constructors, move) {
    Twelve obj1{'1', 'A'};
    Twelve obj2(std::move(obj1));
    ASSERT_EQ(obj2.get_size(), 2);
    ASSERT_EQ(obj2.get_value(), "1A");
    ASSERT_EQ(obj1.get_size(), 0);
    ASSERT_THROW(obj1.get_value(), std::domain_error);
}

TEST(comparison_operators, test1) {
    Twelve obj0("0");
    Twelve obj1("132A");
    Twelve obj2("1AB0");
    ASSERT_TRUE(obj1 == obj1);
    ASSERT_TRUE(obj1 != obj0);
    ASSERT_TRUE(obj1 < obj2);
    ASSERT_TRUE(obj1 > obj0);
    ASSERT_TRUE(obj1 <= obj2);
    ASSERT_TRUE(obj1 >= obj0);

    ASSERT_FALSE(obj1 != obj1);
    ASSERT_FALSE(obj1 == obj0);
    ASSERT_FALSE(obj1 >= obj2);
    ASSERT_FALSE(obj1 <= obj0);
    ASSERT_FALSE(obj1 > obj2);
    ASSERT_FALSE(obj1 < obj0);
}

TEST(assignment_operator, copy) {
    Twelve obj1("ABAB");
    Twelve obj2;
    obj2 = obj1;
    ASSERT_EQ(obj1.get_size(), obj2.get_size());
    ASSERT_EQ(obj1.get_value(), obj2.get_value());
    ASSERT_EQ(obj1, obj2);
}

TEST(assignment_operator, move) {
    Twelve obj1("ABAB");
    Twelve obj2("A123");

    obj2 = std::move(obj1);
    ASSERT_EQ(obj2.get_size(), 4);
    ASSERT_EQ(obj2.get_value(), "ABAB");
    ASSERT_EQ(obj1.get_size(), 0);
    ASSERT_THROW(obj1.get_value(), std::domain_error);
}

TEST(arithmetic_operators, addition) {
    Twelve obj0("0");
    Twelve obj1("AAAAAAAAAA");
    Twelve obj2("5");
    Twelve obj3("AAAAAAAAB3");
    Twelve obj4("2000000000");
    Twelve obj5("10AAAAAAAAA");
    ASSERT_EQ(obj1 + obj0, obj1);
    ASSERT_EQ(obj0 + obj1, obj1);
    ASSERT_EQ(obj1 + obj2, obj3);
    ASSERT_EQ(obj2 + obj1, obj3);
    ASSERT_EQ(obj1 + obj4, obj5);
    ASSERT_EQ(obj4 + obj1, obj5);
}

TEST(arithmetic_operators, subtraction) {
    Twelve obj0("0");
    Twelve obj1("AAAAAAAAAA");
    Twelve obj2("5");
    Twelve obj3("AAAAAAAAA5");
    Twelve obj4("AAAAA0BBBB");
    Twelve obj5("9AAAB");
    ASSERT_EQ(obj1 - obj1, obj0);
    ASSERT_EQ(obj1 - obj0, obj1);
    ASSERT_THROW(obj0 - obj1, std::underflow_error);
    ASSERT_EQ(obj1 - obj2, obj3);
    ASSERT_EQ(obj1 - obj4, obj5);
}

TEST(arithmetic_operators, assignment_add) {
    Twelve obj1("AAAAAAAAAA");
    Twelve obj2 = obj1;
    Twelve obj3("0");
    Twelve obj4("2000000000");

    obj1 += obj3;
    ASSERT_EQ(obj1, obj2);

    obj2 = obj1 + obj4;

    obj1 += obj4;
    ASSERT_EQ(obj1, obj2);
}

TEST(arithmetic_operators, assignment_sub) {
    Twelve obj1("AAAAAAAAAA");
    Twelve obj2 = obj1;
    Twelve obj3("0");
    Twelve obj4("2000000000");

    obj1 -= obj3;
    ASSERT_EQ(obj1, obj2);

    obj2 = obj1 - obj4;

    obj1 -= obj4;
    ASSERT_EQ(obj1, obj2);
    ASSERT_THROW(obj3 -= obj1, std::underflow_error);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}