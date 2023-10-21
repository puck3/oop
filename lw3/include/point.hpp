#pragma once

#include <iostream>

class Point {
private:
    double x, y;

public:
    Point() noexcept;
    Point(double, double) noexcept;
    ~Point() = default;

    double get_x() const noexcept;
    double get_y() const noexcept;
    void set_x(double) noexcept;
    void set_y(double) noexcept;

    bool operator == (const Point&) const noexcept;
    bool operator != (const Point&) const noexcept;

    friend std::ostream& operator << (std::ostream&, const Point&) noexcept;
    friend std::istream& operator >> (std::istream&, Point&);

    friend double seg_length(const Point&, const Point&) noexcept;
    friend bool on_same_line(const Point&, const Point&, const Point&) noexcept;
    friend int cross_product_sign(const Point&, const Point&, const Point&) noexcept;
};
