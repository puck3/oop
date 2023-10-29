#pragma once
#include "point.hpp"

template <std::floating_point T>
class Figure {
protected:
    virtual void throw_if_invalid() const = 0;

public:
    virtual ~Figure() noexcept = default;
    virtual T area() const noexcept = 0;
    virtual Point<T> center() const noexcept = 0;
    virtual void print(std::ostream&) const noexcept = 0;
    explicit virtual operator double() const noexcept = 0;
};
