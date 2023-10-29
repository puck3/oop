#include <iostream>
#include <cmath>
#include "square.hpp"

const double EPS = 1e-7;

void Square::throw_if_invalid() const {
    if (points[0] == points[2] || points[1] == points[3]) {
        throw std::invalid_argument("Figure is not square");
    }
    double side = seg_length(points[0], points[1]);
    for (size_t i{1}; i < size; ++i) {
        if (fabs(seg_length(points[i], points[(i + 1) % size]) - side) > EPS) {
            throw std::invalid_argument("Sides must be equal");
        }
    }
    if (fabs(seg_length(points[0], points[2]) * seg_length(points[0], points[2]) - 2 * side * side) > EPS) {
        if (points[0] == points[2] || points[1] == points[3]) {
            throw std::invalid_argument("Figure is not square");
        }
    }
}

Square::Square(Point& p1, Point& p2, Point& p3, Point& p4) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    this->throw_if_invalid();
}

Square::Square(const Square& other) noexcept {
    *this = other;
}

Square::Square(Square&& other) noexcept {
    *this = other;
}

Point Square::center() const noexcept {
    double x{0};
    double y{0};
    for (size_t i{0}; i < size; ++i) {
        x += points[i].get_x();
        y += points[i].get_y();
    }
    x /= size;
    y /= size;
    return Point(x, y);
}

double Square::area() const noexcept {
    double s = seg_length(points[0], points[1]);
    return s * s;
}

Square::operator double() const noexcept {
    return this->area();
}

Square& Square::operator= (const Square& other) noexcept {
    for (size_t i{0}; i < size; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}

Square& Square::operator= (Square&& other) noexcept {
    for (size_t i{0}; i < size; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}

bool Square::operator== (const Square& other) const noexcept {
    return (fabs(this->area() - other.area()) < EPS);
}

bool Square::operator!= (const Square& other) const noexcept {
    return !(*this == other);
}

void Square::print(std::ostream& os) const noexcept {
    os << "Vertices coordinates:" << std::endl;
    for (size_t i{0}; i < size; ++i) {
        os << points[i] << " ";
    }
    os << std::endl;
}

std::ostream& operator << (std::ostream& os, const Square& square) noexcept {
    square.print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Square& square) {
    for (size_t i{0}; i < square.size; ++i) {
        is >> square.points[i];
    }
    square.throw_if_invalid();
    return is;
}
