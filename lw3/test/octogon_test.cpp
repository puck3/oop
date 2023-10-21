#include<gtest/gtest.h>
#include "octagon.hpp"
#include "point.hpp"

class OctagonTest : public testing::Test {

protected:
    void SetUp() override {
        Point p0, p1{-4, -2}, p2{-4, 2}, p3{-2, 4}, p4{2, 4}, p5{4, 2}, p6{4, -2}, p7{2, -4}, p8{-2, -4}, p9{2, -5}, p10{-3, -6};
        figure1 = Octagon(p1, p2, p3, p4, p5, p6, p7, p8);
        figure2 = Octagon(p1, p2, p3, p4, p5, p6, p9, p10);
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
        figure1.~Octagon();
        figure2.~Octagon();
    }

    Point p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
    Octagon figure1, figure2;
};

TEST_F(OctagonTest, ThrowTest) {
    ASSERT_THROW(Octagon(p1, p3, p2, p4, p5, p6, p7, p8), std::invalid_argument);
    ASSERT_THROW(Octagon(p1, p1, p1, p4, p5, p6, p7, p8), std::invalid_argument);
    ASSERT_THROW(Octagon(p1, p3, p2, p4, p5, p6, p7, p8), std::invalid_argument);
}

TEST_F(OctagonTest, AreaTest) {
    ASSERT_DOUBLE_EQ(figure1.area(), 56);
    ASSERT_DOUBLE_EQ(figure2.area(), 66.5);
}

TEST_F(OctagonTest, CenterTest) {
    ASSERT_EQ(figure1.center(), p0);
    ASSERT_EQ(figure2.center(), Point(-0.125, -0.375));
}

TEST_F(OctagonTest, DoubleCastTest) {
    ASSERT_DOUBLE_EQ(double(figure1), figure1.area());
    ASSERT_DOUBLE_EQ(double(figure2), figure2.area());
}

TEST_F(OctagonTest, EqTest) {
    Octagon figure3{figure1};
    ASSERT_EQ(figure1, figure3);
    ASSERT_NE(figure1, figure2);
}
