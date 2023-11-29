#include<gtest/gtest.h>

#include "List.hpp"
#include "Allocator.hpp"

TEST(TestIterator, TestConstructor) {
    auto node = new Node<int>(5);
    auto it = List<int>::iterator(node);
    ASSERT_EQ(*it, 5);
    ASSERT_FALSE(++it);
    delete node;
}

TEST(TestIterator, TestOperatorAsterisk) {
    List<int> list = {1, 2, 3, 4};
    auto it = list.begin();
    ASSERT_EQ(*it, 1);
    it = list.end();
    ASSERT_FALSE(it);
}

TEST(TestIterator, TestIncrementDecrement) {
    List<int> list = {1, 2, 3, 4, 5};
    auto it = list.begin();

    ++it;
    ASSERT_EQ(*it, 2);
    auto new_it = ++it;
    ASSERT_EQ(*new_it, 3);

    it++;
    ASSERT_EQ(*it, 4);
    new_it = it++;
    ASSERT_EQ(*new_it, 4);

    --it;
    ASSERT_EQ(*it, 4);
    new_it = --it;
    ASSERT_EQ(*new_it, 3);

    it--;
    ASSERT_EQ(*it, 2);
    new_it = it--;
    ASSERT_EQ(*new_it, 2);
}

TEST(TestIterator, TestOperatorEqual) {
    List<int> list = {1, 2, 3, 4, 5};
    auto first = list.begin();
    auto second = list.begin();

    ASSERT_EQ(first, second);
    second++;
    ASSERT_NE(first, second);
}

TEST(TestIterator, TestOperatorBool) {
    auto it = List<int>::iterator(nullptr);
    ASSERT_FALSE(it);
    ASSERT_THROW(*it, std::runtime_error);
    ASSERT_THROW(++it, std::runtime_error);
    ASSERT_THROW(--it, std::runtime_error);
}

TEST(TestConstIterator, TestConstructor) {
    auto node = new Node<int>(5);
    auto it = List<int>::const_iterator(node);
    ASSERT_EQ(*it, 5);
    ASSERT_FALSE(++it);
    delete node;
}

TEST(TestConstIterator, TestOperatorAsterisk) {
    List<int> list = {1, 2, 3, 4};
    auto it = list.cbegin();
    ASSERT_EQ(*it, 1);
    it = list.cend();
    ASSERT_FALSE(it);
}

TEST(TestConstIterator, TestIncrementDecrement) {
    List<int> list = {1, 2, 3, 4, 5};
    auto it = list.cbegin();

    ++it;
    ASSERT_EQ(*it, 2);
    auto new_it = ++it;
    ASSERT_EQ(*new_it, 3);

    it++;
    ASSERT_EQ(*it, 4);
    new_it = it++;
    ASSERT_EQ(*new_it, 4);

    --it;
    ASSERT_EQ(*it, 4);
    new_it = --it;
    ASSERT_EQ(*new_it, 3);

    it--;
    ASSERT_EQ(*it, 2);
    new_it = it--;
    ASSERT_EQ(*new_it, 2);
}

TEST(TestConstIterator, TestOperatorEqual) {
    List<int> list = {1, 2, 3, 4, 5};

    auto first = list.cbegin();
    auto second = list.cbegin();

    ASSERT_EQ(first, second);
    second++;
    ASSERT_NE(first, second);
}

TEST(TestConstIterator, TestOperatorBool) {
    auto it = List<int>::const_iterator(nullptr);
    ASSERT_FALSE(it);
    ASSERT_THROW(*it, std::runtime_error);
    ASSERT_THROW(++it, std::runtime_error);
    ASSERT_THROW(--it, std::runtime_error);
}
