#include<gtest/gtest.h>
#include "triangle.hpp"
#include "point.hpp"

class TriangleTest : public testing::Test {
protected:
    Point<double> p0, p1{0, 4}, p2{3, 0}, p3{4, 2}, p4{6, 5}, p5{8, 2}, p6{0, 1};
    Triangle<double> figure1{p0, p1, p2}, figure2{p3, p4, p5}, figure3{p0, p1, p4};
};

TEST_F(TriangleTest, ThrowTest) {
    ASSERT_THROW(Triangle<double>(p0, p1, p6), std::invalid_argument);
}

TEST_F(TriangleTest, AreaTest) {
    ASSERT_DOUBLE_EQ(figure1.area(), 6);
    ASSERT_DOUBLE_EQ(figure2.area(), 6);
}

TEST_F(TriangleTest, CenterTest) {
    ASSERT_EQ(figure1.center(), Point<double>(1, 4.0 / 3.0));
    ASSERT_EQ(figure2.center(), Point<double>(6, 3));
}

TEST_F(TriangleTest, DoubleCastTest) {
    ASSERT_DOUBLE_EQ(double(figure1), figure1.area());
    ASSERT_DOUBLE_EQ(double(figure2), figure2.area());
}

TEST_F(TriangleTest, EqTest) {
    ASSERT_EQ(figure1, figure2);
    ASSERT_NE(figure1, figure3);
}
