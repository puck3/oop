#include<gtest/gtest.h>
#include "square.hpp"
#include "point.hpp"

class SquareTest : public testing::Test {

protected:
    void SetUp() override {
        Point p0, p1{-3, -3}, p2{-3, 4}, p3{4, 4}, p4{4, -3}, p5{2, 1}, p6{3, -1}, p7{1, -2}, p8{2, 0}, p9{1,2};
        figure1 = Square(p1, p2, p3, p4);
        figure2 = Square(p0, p5, p6, p7);
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
        figure1.~Square();
        figure2.~Square();
    }

    Point p0, p1, p2, p3, p4, p5, p6, p7, p8, p9;
    Square figure1, figure2;
};

TEST_F(SquareTest, ThrowTest) {
    ASSERT_THROW(Square(p1, p2, p1, p4), std::invalid_argument);
    ASSERT_THROW(Square(p1, p2, p0, p4), std::invalid_argument);
    ASSERT_THROW(Square(p0, p7, p8, p9), std::invalid_argument);
}

TEST_F(SquareTest, AreaTest) {
    ASSERT_DOUBLE_EQ(figure1.area(), 49);
    ASSERT_DOUBLE_EQ(figure2.area(), 5);
}

TEST_F(SquareTest, CenterTest) {
    ASSERT_EQ(figure1.center(), Point(0.5, 0.5));
    ASSERT_EQ(figure2.center(), Point(1.5, -0.5));
}

TEST_F(SquareTest, DoubleCastTest) {
    ASSERT_DOUBLE_EQ(double(figure1), figure1.area());
    ASSERT_DOUBLE_EQ(double(figure2), figure2.area());
}

TEST_F(SquareTest, EqTest) {
    Square figure3{figure1};
    ASSERT_EQ(figure1, figure3);
    ASSERT_NE(figure1, figure2);
}
