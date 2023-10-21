#pragma once
#include "point.hpp"

class Figure {
protected:
    virtual void throw_if_invalid() const = 0;

public:
    virtual ~Figure() noexcept = default;
    virtual double area() const noexcept = 0;
    virtual Point center() const noexcept = 0;
    virtual void print(std::ostream&) const noexcept = 0;
    explicit virtual operator double() const noexcept = 0;
};
