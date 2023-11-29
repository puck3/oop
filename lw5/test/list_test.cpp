#include <gtest/gtest.h>
#include <vector>
#include "Allocator.hpp"
#include "List.hpp"

TEST(TestList, TestDefaultConstructor) {
    List<int, Allocator<Node<int>, 10>> list;
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
    ASSERT_EQ(list.begin(), list.end());
}

TEST(TestList, TestCountValueConstructor) {
    List<int, Allocator<Node<int>, 10>> list(7, 2);
    ASSERT_EQ(list.size(), 7);
    ASSERT_EQ(list.max_size(), 10);
    for (auto el : list) {
        ASSERT_EQ(el, 2);
    }
}

TEST(TestList, TestCountDefaultValueConstructor) {
    List<int> list(20);
    ASSERT_EQ(list.size(), 20);
    for (auto el : list) {
        ASSERT_EQ(el, 0);
    }
}

TEST(TestList, TestTwoIteratorsConstructor) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
    List<int> list(v.begin(), v.end());
    ASSERT_EQ(list.size(), v.size());
    size_t i{0};
    for (auto el : list) {
        ASSERT_EQ(el, v[i]);
        ++i;
    }
}

TEST(TestList, TestIListConstructor) {
    std::initializer_list<char> ilist = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    List<char> list{ilist};
    ASSERT_EQ(list.size(), ilist.size());
    size_t i{0};
    for (auto el : list) {
        ASSERT_EQ(el, *(ilist.begin() + i));
        ++i;
    }
}

TEST(TestList, TestCopyConstructor) {
    List<int> other = {1, 2, 3, 4, 5, 6};
    List<int> list(other);
    ASSERT_EQ(list.size(), other.size());

    for (auto it1 = list.begin(), it2 = other.begin(); it1 != list.end() && it2 != other.end(); ++it1, ++it2) {
        ASSERT_EQ(*it1, *it2);
    }
}

TEST(TestList, TestMoveConstructor) {
    List<int> other = {1, 2, 3, 4, 5, 6};
    List<int> list(move(other));
    ASSERT_EQ(list.size(), 6);
    ASSERT_EQ(other.size(), 0);
    int val{1};
    for (auto it1 = list.begin(); it1 != list.end(); ++it1) {
        ASSERT_EQ(*it1, val++);
    }
}

TEST(TestList, TestAssignment) {
    List<int> other = {1, 2, 3, 4, 5, 6, 7, 8};
    List<int> list;
    list = other;
    ASSERT_EQ(list.size(), other.size());
    for (auto it1 = list.begin(), it2 = other.begin(); it1 != list.end() && it2 != other.end(); ++it1, ++it2) {
        ASSERT_EQ(*it1, *it2);
    }
}

TEST(TestList, TestMoveAssignment) {
    List<int> other = {1, 2, 3, 4, 5, 6, 7, 8};
    List<int> list;
    list = move(other);
    ASSERT_EQ(list.size(), 8);
    ASSERT_EQ(other.size(), 0);
    int val{1};
    for (auto it1 = list.begin(); it1 != list.end(); ++it1) {
        ASSERT_EQ(*it1, val++);
    }
}

TEST(TestList, TestIListAssignment) {
    std::initializer_list<int> ilist = {1, 2, 3, 4, 5, 6, 7, 8};
    List<int> list;
    list = ilist;
    ASSERT_EQ(list.size(), ilist.size());
    auto it1 = list.begin();
    auto it2 = ilist.begin();
    for (; it1 != list.end() && it2 != ilist.end(); ++it1, ++it2) {
        ASSERT_EQ(*it1, *it2);
    }
}

TEST(TestList, TestAssignCountValues) {
    List<int> list = {1, 2, 3, 4};
    list.assign(5, 2);
    ASSERT_EQ(list, List<int>(5, 2));
}

TEST(TestList, TestAssignTwoIterators) {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    List<int> list(10);
    list.assign(v.begin(), v.end());
    ASSERT_EQ(list, List<int>(v.begin(), v.end()));
}

TEST(TestList, TestAssignIList) {
    std::initializer_list<int> ilist = {1, 2, 3, 4, 5, 6, 7, 8};
    List<int> list(20);
    list.assign(ilist);
    ASSERT_EQ(list, List<int>(ilist));
}

TEST(TestList, TestFrontBack) {
    List<int> list = {1, 2, 3};
    auto it{list.begin()};
    ASSERT_EQ(list.front(), *it);
    ++++it;
    ASSERT_EQ(list.back(), *it);
}

TEST(TestList, TestEmpty) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    list = {1, 2, 3, 4, 5};
    ASSERT_FALSE(list.empty());
}

TEST(TestList, TestSize) {
    List<int> list;
    ASSERT_EQ(list.size(), 0);
    list = {1, 2, 3};
    ASSERT_EQ(list.size(), 3);
}

TEST(TestList, TestMaxSize) {
    List<int, Allocator<Node<int>, 15>> list;
    ASSERT_EQ(list.max_size(), 15);
}

TEST(TestList, TestClear) {
    List<int> list = {1, 2, 3, 4, 5, 6, 7, 8};
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(TestList, TestInsertValue) {
    List<int> list = {1, 2, 3};
    auto it = list.insert(list.begin(), 5);
    ASSERT_EQ(list, List<int>({5, 1, 2, 3}));
    ASSERT_EQ(*it, list.front());
    it = list.insert(list.end(), 10);
    ASSERT_EQ(list, List<int>({5, 1, 2, 3, 10}));
    ASSERT_EQ(*it, list.back());
}

TEST(TestList, TestInsertCountValue) {
    List<int> list = {1, 2, 3};
    list.insert(list.begin(), 2, 5);
    ASSERT_EQ(list, List<int>({5, 5, 1, 2, 3}));
    list.insert(list.end(), 3, 10);
    ASSERT_EQ(list, List<int>({5, 5, 1, 2, 3, 10, 10, 10}));
}

TEST(TestList, TestInsertTwoIterators) {
    std::vector<int> v = {4, 5, 6};
    List<int> list = {1, 2, 3};
    list.insert(list.begin(), v.begin(), v.end());
    ASSERT_EQ(list, List<int>({4, 5, 6, 1, 2, 3}));
}

TEST(TestList, TestInsertInitializerList) {
    std::initializer_list<int> ilist = {1, 2};
    List<int> list = {1, 2, 3};
    list.insert(list.begin(), ilist);
    ASSERT_EQ(list, List<int>({1, 2, 1, 2, 3}));
}

TEST(TestList, TestErase) {
    List<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list.erase(list.begin());
    ASSERT_EQ(list, List<int>({2, 3, 4, 5, 6, 7, 8, 9}));
    list.erase(++list.begin());
    ASSERT_EQ(list, List<int>({2, 4, 5, 6, 7, 8, 9}));
}

TEST(TestList, TestPushBack) {
    List<int> list = {1, 2, 3};
    list.push_back(10);
    ASSERT_EQ(list, List<int>({1, 2, 3, 10}));

    list.push_back(11);
    ASSERT_EQ(list, List<int>({1, 2, 3, 10, 11}));
}

TEST(TestList, TestPopBack) {
    List<int> list = {1, 2, 3, 4, 5};
    list.pop_back();
    ASSERT_EQ(list, List<int>({1, 2, 3, 4}));
    list.pop_back();
    ASSERT_EQ(list, List<int>({1, 2, 3}));
}

TEST(TestList, TestPushFront) {
    List<int> list = {1, 2, 3, 4, 5};
    list.push_front(10);
    ASSERT_EQ(list, List<int>({10, 1, 2, 3, 4, 5}));
    list.push_front(11);
    ASSERT_EQ(list, List<int>({11, 10, 1, 2, 3, 4, 5}));
}

TEST(TestList, TestPopFront) {
    List<int> list = {1, 2, 3, 4, 5};
    list.pop_front();
    ASSERT_EQ(list, List<int>({2, 3, 4, 5}));
    list.pop_front();
    ASSERT_EQ(list, List<int>({3, 4, 5}));
}

TEST(TestList, TestEqualOperator) {
    List<int> list = {1, 2, 3, 4, 5, 6, 7, 8};
    List<int> other = list;
    ASSERT_EQ(list, other);
    other = {1, 2, 3, 4};
    ASSERT_NE(list, other);
}

TEST(TestList, TestSwap) {
    List<int> list1 = {1, 2, 3};
    List<int> list2 = {5, 6, 7};
    swap(list1, list2);
    ASSERT_EQ(list1, List<int>({5, 6, 7}));
    ASSERT_EQ(list2, List<int>({1, 2, 3}));
}
