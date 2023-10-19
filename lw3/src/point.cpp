#include "point.hpp"
#include <cmath>

const double EPS = 1e-7;

Point::Point() : x{0}, y{0} {}

Point::Point(double x, double y) : x{x}, y{y} {}

Point::Point(const Point& other) : x{other.x}, y{other.y} {}

Point& Point::operator =(const Point& other) noexcept {
    x = other.x;
    y = other.y;
    return *this;
}

bool Point::operator == (const Point& other) const noexcept {
    return (x == other.x && y == other.y);
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
    return (seg12 + seg13 - seg23 < EPS) || (seg12 + seg23 - seg13 < EPS) || (seg13 + seg23 - seg12 < EPS);
}
