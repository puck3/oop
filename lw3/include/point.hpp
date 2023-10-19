#pragma once

#include <iostream>

class Point {
private:
    double x, y;
public:
    Point();
    Point(double, double);
    Point(const Point&);
    ~Point() = default;

    Point& operator =(const Point&) noexcept;
    bool operator == (const Point&) const noexcept;

    friend double seg_length(const Point&, const Point&) noexcept;
    friend bool on_same_line(const Point&, const Point&, const Point&) noexcept;

    friend std::ostream& operator << (std::ostream&, const Point&) noexcept;
    friend std::istream& operator >> (std::istream&, Point&);
};
