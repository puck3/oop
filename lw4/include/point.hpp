#pragma once
#include <iostream>
#include <cmath>

const double EPS = 1e-7;

template <std::floating_point T>
class Point {
private:
    T x, y;

public:
    Point() noexcept : x{0}, y{0} {}
    Point(const T& _x, const T& _y) noexcept : x{_x}, y{_y} {}
    virtual ~Point() = default;

    T get_x() const noexcept {
        return x;
    }

    T get_y() const noexcept {
        return y;
    }

    void set_x(const T& _x) noexcept {
        x = _x;
    }

    void set_y(const T& _y) noexcept {
        y = _y;
    }

    bool operator == (const Point<T>& other) const noexcept {
        return (fabs(x - other.x) < EPS) && (fabs(y - other.y) < EPS);
    }

    bool operator != (const Point<T>& other) const noexcept {
        return !(*this == other);
    }

    friend std::ostream& operator << (std::ostream& os, const Point<T>& p) noexcept {
        os << "(" << p.x << "; " << p.y << ")";
        return os;
    }

    friend std::istream& operator >> (std::istream& is, Point<T>& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend T seg_length(const Point<T>& p1, const Point<T>& p2) noexcept {
        T dx = p1.x - p2.x, dy = p1.y - p2.y;
        return sqrt(dx * dx + dy * dy);
    }

    friend bool on_same_line(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) noexcept {
        T seg12 = seg_length(p1, p2), seg13 = seg_length(p1, p3), seg23 = seg_length(p2, p3);
        return (fabs(seg12 + seg13 - seg23) < EPS) || (fabs(seg12 + seg23 - seg13) < EPS) || (fabs(seg13 + seg23 - seg12) < EPS);
    }

    friend int cross_product_sign(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) noexcept {
        if ((p1.x - p2.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p1.y - p2.y) > 0) return 1;
        else return -1;
    }
};
