#include <iostream>
#include <cmath>
#include "triangle.hpp"

const double EPS = 1e-7;

void Triangle::throw_if_invalid() const {
    if (on_same_line(p1, p2, p3)) {
        throw std::invalid_argument("3 points lie on the same line");
    }
}

Triangle::Triangle(Point& p1, Point& p2, Point& p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->throw_if_invalid();
}

Triangle::Triangle(const Triangle& other) noexcept {
    *this = other;
}

Triangle::Triangle(Triangle&& other) noexcept {
    *this = other;
}

Point Triangle::center() const noexcept {
    double x = (p1.get_x() + p2.get_x() + p3.get_x()) / 3;
    double y = (p1.get_y() + p2.get_y() + p3.get_y()) / 3;
    return Point(x, y);
}

double Triangle::area() const noexcept {
    double s = fabs(0.5 * ((p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y()) - (p3.get_x() - p1.get_x()) * (p2.get_y() - p1.get_y())));
    return s;
}

Triangle::operator double() const noexcept {
    return this->area();
}

Triangle& Triangle::operator= (const Triangle& other) noexcept {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    return *this;
}

Triangle& Triangle::operator= (Triangle&& other) noexcept {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    return *this;
}

bool Triangle::operator== (const Triangle& other) const noexcept {
    return (fabs(this->area() - other.area()) < EPS);
}

bool Triangle::operator!= (const Triangle& other) const noexcept {
    return !(*this == other);
}

void Triangle::print(std::ostream& os) const noexcept {
    os << "Vertices coordinates:" << std::endl;
    os << p1 << " " << p2 << " " << p3 << std::endl;
}

std::ostream& operator << (std::ostream& os, const Triangle& triangle) noexcept {
    triangle.print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Triangle& triangle) {
    is >> triangle.p1 >> triangle.p2 >> triangle.p3;
    triangle.throw_if_invalid();
    return is;
}
