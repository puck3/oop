#include<gtest/gtest.h>
#include "point.hpp"

class PointTest : public testing::Test {
protected:
    void SetUp() override {
        p0 = Point<double>();
        p1 = Point<double>(1, 2);
        p2 = Point<double>(2, 3);
        p3 = Point<double>(2, 2);
        p4 = Point<double>(3, 4);
    }

    Point<double> p0, p1, p2, p3, p4;

};

TEST_F(PointTest, GetSetTest) {
    ASSERT_DOUBLE_EQ(p1.get_x(), 1);
    ASSERT_DOUBLE_EQ(p2.get_x(), 2);

    ASSERT_DOUBLE_EQ(p1.get_y(), 2);
    ASSERT_DOUBLE_EQ(p2.get_y(), 3);

    p0.set_x(1);
    p0.set_y(2);
    ASSERT_DOUBLE_EQ(p0.get_x(), 1);
    ASSERT_DOUBLE_EQ(p0.get_y(), 2);
}

TEST_F(PointTest, EqTest) {
    Point<double> p = p1;
    ASSERT_EQ(p, p1);
    ASSERT_NE(p, p2);
}

TEST_F(PointTest, SegLengthTest) {
    ASSERT_DOUBLE_EQ(seg_length(p1, p3), 1);
    ASSERT_DOUBLE_EQ(seg_length(p2, p3), 1);
}

TEST_F(PointTest, OnSameLineTest) {
    ASSERT_TRUE(on_same_line(p1, p2, p4));
    ASSERT_FALSE(on_same_line(p1, p2, p3));
}

TEST_F(PointTest, CrossProductSignTest) {
    ASSERT_EQ(cross_product_sign(p1, p2, p3), 1);
    ASSERT_EQ(cross_product_sign(p1, p3, p2), -1);
}
