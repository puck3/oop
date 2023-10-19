#pragma once

#include "point.hpp"

class Figure {
protected:
    int points_qty;
    Point* points;
public:
    Figure();
    virtual ~Figure() noexcept;
    virtual double area() const noexcept = 0;
    virtual double perimeter() const noexcept = 0;
    virtual Point center() const noexcept = 0;
};
