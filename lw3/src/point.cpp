#include "point.hpp"
#include <cmath>

const double EPS = 1e-7;

Point::Point() noexcept : x{0}, y{0} {}

Point::Point(double x, double y) noexcept : x{x}, y{y} {}

double Point::get_x() const noexcept {
    return x;
}

double Point::get_y() const noexcept {
    return y;
}

void Point::set_x(double x) noexcept {
    this->x = x;
}

void Point::set_y(double y) noexcept {
    this->y = y;
}

bool Point::operator == (const Point& other) const noexcept {
    return (fabs(x - other.x) < EPS) && (fabs(y - other.y) < EPS);
}

bool Point::operator != (const Point& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator << (std::ostream& os, const Point& p) noexcept {
    os << "(" << p.x << "; " << p.y << ")";
    return os;
}

std::istream& operator >> (std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

double seg_length(const Point& p1, const Point& p2) noexcept {
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

bool on_same_line(const Point& p1, const Point& p2, const Point& p3) noexcept {
    double seg12 = seg_length(p1, p2), seg13 = seg_length(p1, p3), seg23 = seg_length(p2, p3);
    return (fabs(seg12 + seg13 - seg23) < EPS) || (fabs(seg12 + seg23 - seg13) < EPS) || (fabs(seg13 + seg23 - seg12) < EPS);
}

int cross_product_sign(const Point& p1, const Point& p2, const Point& p3) noexcept {
    if ((p1.x - p2.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p1.y - p2.y) > 0) return 1;
    else return -1;
}
