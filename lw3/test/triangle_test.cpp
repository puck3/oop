#include<gtest/gtest.h>
#include "triangle.hpp"
#include "point.hpp"

class TriangleTest : public testing::Test {

protected:
    void SetUp() override {
        Point p0, p1{0, 4}, p2{3, 0}, p3{4, 2}, p4{6, 5}, p5{8, 2}, p6{0, 1};
        figure1 = Triangle(p0, p1, p2);
        figure2 = Triangle(p3, p4, p5);
        Triangle figure3{p0, p1, p4};

    }

    void TearDown() override {
        p0.~Point();
        p1.~Point();
        p2.~Point();
        p3.~Point();
        p4.~Point();
        p5.~Point();
        p6.~Point();
        figure1.~Triangle();
        figure2.~Triangle();
        figure3.~Triangle();
    }

    Point p0, p1, p2, p3, p4, p5, p6;
    Triangle figure1, figure2, figure3;
};

TEST_F(TriangleTest, ThrowTest) {
    ASSERT_THROW(Triangle(p0, p1, p6), std::invalid_argument);
}

TEST_F(TriangleTest, AreaTest) {
    ASSERT_DOUBLE_EQ(figure1.area(), 6);
    ASSERT_DOUBLE_EQ(figure2.area(), 6);
}

TEST_F(TriangleTest, CenterTest) {
    ASSERT_EQ(figure1.center(), Point(1, 4.0 / 3.0));
    ASSERT_EQ(figure2.center(), Point(6, 3));
}

TEST_F(TriangleTest, DoubleCastTest) {
    ASSERT_DOUBLE_EQ(double(figure1), figure1.area());
    ASSERT_DOUBLE_EQ(double(figure2), figure2.area());
}

TEST_F(TriangleTest, EqTest) {
    ASSERT_EQ(figure1, figure2);
    ASSERT_NE(figure1, figure3);
}
