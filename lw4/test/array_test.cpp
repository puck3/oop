#include<gtest/gtest.h>
#include "figures_array.hpp"
#include "point.hpp"
#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"


class ArrayTest : public testing::Test {
protected:
    void SetUp() override {
        arr = Array<std::shared_ptr<Figure<double>>>();
    }

    Array<std::shared_ptr<Figure<double>>> arr;
    Point<double> p0{}, p1{0, 4}, p2{3, 0}, p3{3, -4}, p4{0, -6}, p5{-4, -6}, p6{-6, -3}, p7{-6, 2}, p8{-3, 4}, p9{4, 4}, p10{4, 0};
    Triangle<double> triangle{p0, p1, p2};
    Square<double> square{p0, p1, p9, p10};
    Octagon<double> octagon{p1, p2, p3, p4, p5, p6, p7, p8};
    std::shared_ptr<Triangle<double>> triangle_ptr = std::make_shared<Triangle<double>>(triangle);
    std::shared_ptr<Square<double>> square_ptr = std::make_shared<Square<double>>(square);
    std::shared_ptr<Octagon<double>> octagon_ptr = std::make_shared<Octagon<double>>(octagon);
};

TEST_F(ArrayTest, PushBackTest) {
    arr.push_back(triangle_ptr);
    arr.push_back(square_ptr);
    arr.push_back(octagon_ptr);

    ASSERT_EQ(arr.length(), 3);
    ASSERT_EQ(arr[0], triangle_ptr);
    ASSERT_EQ(arr[1], square_ptr);
    ASSERT_EQ(arr[2], octagon_ptr);
}

TEST_F(ArrayTest, PopBackTest) {
    arr.push_back(triangle_ptr);
    arr.push_back(square_ptr);
    arr.push_back(octagon_ptr);

    ASSERT_EQ(arr.pop_back(), octagon_ptr);
    ASSERT_EQ(arr.pop_back(), square_ptr);
    ASSERT_EQ(arr.pop_back(), triangle_ptr);
    ASSERT_EQ(arr.length(), 0);
}

TEST_F(ArrayTest, EraseTest) {
    arr.push_back(triangle_ptr);
    arr.push_back(square_ptr);
    arr.push_back(octagon_ptr);

    arr.erase(1);
    ASSERT_EQ(arr[0], triangle_ptr);
    ASSERT_EQ(arr[1], octagon_ptr);
    ASSERT_EQ(arr.length(), 2);
}

TEST_F(ArrayTest, AreaTest) {
    arr.push_back(triangle_ptr);
    arr.push_back(square_ptr);
    arr.push_back(octagon_ptr);

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