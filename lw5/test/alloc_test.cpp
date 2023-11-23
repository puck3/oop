#include <gtest/gtest.h>
#include <map>
#include "Allocator.hpp"

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

TEST(TestAlloc, SimpleTest) {
    Allocator<int, 1> alloc{};
    ASSERT_EQ(alloc.max_size(), 1);
    int* ptr = alloc.allocate(1);
    alloc.construct(ptr, 5);
    ASSERT_EQ(*ptr, 5);
    alloc.destroy(ptr);
    alloc.deallocate(ptr, 1);
}

TEST(TestAlloc, SimpleArrayTest) {
    Allocator<int, 10> alloc{};
    ASSERT_EQ(alloc.max_size(), 10);
    int* arr = alloc.allocate(10);
    for (size_t i{0}; i < 10; ++i) {
        alloc.construct(arr + i, i);
    }
    for (size_t i{0}; i < 10; ++i) {
        ASSERT_EQ(arr[i], i);
    }
    for (size_t i{0}; i < 10; ++i) {
        alloc.destroy(arr + i);
    }
    alloc.deallocate(arr, 10);
}

TEST(TestAlloc, MapTest) {
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 10>> myMap;
    for (int i = 0; i < 10; ++i) {
        myMap.emplace(i, factorial(i));
    }
    for (const auto& pair : myMap) {
        ASSERT_EQ(pair.second, factorial(pair.first));
    }
}

TEST(TestAlloc, ThrowTest) {
    Allocator<int, 1> alloc{};
    ASSERT_EQ(alloc.max_size(), 1);
    ASSERT_THROW(alloc.allocate(10), std::bad_alloc);
}
