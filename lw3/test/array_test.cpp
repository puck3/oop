#include<gtest/gtest.h>
#include "figures_array.hpp"
#include "point.hpp"
#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"


class ArrayTest : public testing::Test {

protected:
    void SetUp() override {
        p0 = Point();
        p1 = Point(0, 4);
        p2 = Point(3, 0);
        p3 = Point(3, -4);
        p4 = Point(0, -6);
        p5 = Point(-4, -6);
        p6 = Point(-6, -3);
        p7 = Point(-6, 2);
        p8 = Point(-3, 4);
        p9 = Point(4, 4);
        p10 = Point(4, 0);
        triangle = Triangle(p0, p1, p2);
        square = Square(p0, p1, p9, p10);
        octagon = Octagon(p1, p2, p3, p4, p5, p6, p7, p8);
        arr = FiguresArray();
    }

    void TearDown() override {
        p0.~Point();
        p1.~Point();
        p2.~Point();
        p3.~Point();
        p4.~Point();
        p5.~Point();
        p6.~Point();
        p7.~Point();
        p8.~Point();
        p9.~Point();
        p10.~Point();
        triangle.~Triangle();
        arr.~FiguresArray();
    }

    FiguresArray arr;
    Point p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
    Triangle triangle;
    Square square;
    Octagon octagon;
};

TEST_F(ArrayTest, PushBackTest) {
    arr.push_back(&triangle);
    arr.push_back(&square);
    arr.push_back(&octagon);

    ASSERT_EQ(arr.length(), 3);
    ASSERT_EQ(arr[0], &triangle);
    ASSERT_EQ(arr[1], &square);
    ASSERT_EQ(arr[2], &octagon);
}

TEST_F(ArrayTest, PopBackTest) {
    arr.push_back(&triangle);
    arr.push_back(&square);
    arr.push_back(&octagon);

    ASSERT_EQ(arr.pop_back(), &octagon);
    ASSERT_EQ(arr.pop_back(), &square);
    ASSERT_EQ(arr.pop_back(), &triangle);
    ASSERT_EQ(arr.length(), 0);
}

TEST_F(ArrayTest, EraseTest) {
    arr.push_back(&triangle);
    arr.push_back(&square);
    arr.push_back(&octagon);

    arr.erase(1);
    ASSERT_EQ(arr[0], &triangle);
    ASSERT_EQ(arr[1], &octagon);
    ASSERT_EQ(arr.length(), 2);
}

TEST_F(ArrayTest, AreaTest) {
    arr.push_back(&triangle);
    arr.push_back(&square);
    arr.push_back(&octagon);

    double area = triangle.area() + square.area() + octagon.area();
    ASSERT_DOUBLE_EQ(arr.area(), area);
    arr.pop_back();
    area -= octagon.area();
    ASSERT_DOUBLE_EQ(arr.area(), area);
    arr.pop_back();
    arr.pop_back();
    ASSERT_DOUBLE_EQ(arr.area(), 0);
}

TEST_F(ArrayTest, ThrowTest) {
    ASSERT_THROW(arr.pop_back(), std::domain_error);
    ASSERT_THROW(arr.erase(2), std::out_of_range);
    ASSERT_THROW(arr[4], std::out_of_range);
}