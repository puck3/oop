#include <iostream>
#include <cmath>
#include "octagon.hpp"

const double EPS = 1e-7;

void Octagon::throw_if_invalid() const {
    if (on_same_line(points[0], points[1], points[2])) {
        throw std::invalid_argument("3 points lie on the same line");
    }
    int sign = cross_product_sign(points[0], points[1], points[2]);
    for (size_t i{1}; i < size; ++i) {
        if (on_same_line(points[0], points[1], points[2])) {
            throw std::invalid_argument("3 points lie on the same line");
        }
        if (cross_product_sign(points[i], points[(i + 1) % size], points[(i + 2) % size]) != sign) {
            throw std::invalid_argument("Figure is not convex");
        }
    }
}

Octagon::Octagon(Point& p1, Point& p2, Point& p3, Point& p4, Point& p5, Point& p6, Point& p7, Point& p8) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    points[5] = p6;
    points[6] = p7;
    points[7] = p8;
    this->throw_if_invalid();
}

Octagon::Octagon(const Octagon& other) noexcept {
    *this = other;
}

Octagon::Octagon(Octagon&& other) noexcept {
    *this = other;
}


Point Octagon::center() const noexcept {
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

double Octagon::area() const noexcept {
    double s{0};
    for (size_t i{0}; i < size; ++i) {
        s += points[i].get_x() * (points[(i + 1) % size].get_y() - points[(size + i - 1) % size].get_y());
    }
    s /= 2;
    return fabs(s);
}

Octagon::operator double() const noexcept {
    return this->area();
}

Octagon& Octagon::operator= (const Octagon& other) noexcept {
    for (size_t i{0}; i < size; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}

Octagon& Octagon::operator= (Octagon&& other) noexcept {
    for (size_t i{0}; i < size; ++i) {
        points[i] = other.points[i];
    }
    return *this;
}

bool Octagon::operator== (const Octagon& other) const noexcept {
    return (fabs(this->area() - other.area()) < EPS);
}

bool Octagon::operator!= (const Octagon& other) const noexcept {
    return !(*this == other);
}

void Octagon::print(std::ostream& os) const noexcept {
    os << "Vertices coordinates:" << std::endl;
    for (size_t i{0}; i < size; ++i) {
        os << points[i] << " ";
    }
    os << std::endl;
}

std::ostream& operator << (std::ostream& os, const Octagon& octagon) noexcept {
    octagon.print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Octagon& octagon) {
    for (size_t i{0}; i < octagon.size; ++i) {
        is >> octagon.points[i];
    }
    octagon.throw_if_invalid();
    return is;
}
