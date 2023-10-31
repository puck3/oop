#pragma once
#include "figure.hpp"
#include "point.hpp"

template <std::floating_point T>
class Triangle final : public Figure<T> {
private:
    Point<T> p1, p2, p3;

protected:
    virtual void throw_if_invalid() const override {
        if (on_same_line(p1, p2, p3)) {
            throw std::invalid_argument("3 points lay on the same line");
        }
    }

public:
    Triangle() noexcept = default;

    Triangle(Point<T>& _p1, Point<T>& _p2, Point<T>& _p3) : p1{_p1}, p2{_p2}, p3{_p3} {
        this->throw_if_invalid();
    }

    ~Triangle() noexcept = default;

    virtual T area() const noexcept override {
        T s = fabs(0.5 * ((p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y()) - (p3.get_x() - p1.get_x()) * (p2.get_y() - p1.get_y())));
        return s;
    }

    virtual Point<T> center() const noexcept override {
        T x = (p1.get_x() + p2.get_x() + p3.get_x()) / 3;
        T y = (p1.get_y() + p2.get_y() + p3.get_y()) / 3;
        return Point<T>(x, y);
    }

    virtual void print(std::ostream& os) const noexcept override {
        os << "Vertices coordinates:" << std::endl;
        os << p1 << " " << p2 << " " << p3 << std::endl;
    }

    explicit virtual operator double() const noexcept override {
        return this->area();
    }

    bool operator == (const Triangle<T>& other) const noexcept {
        return (fabs(this->area() - other.area()) < EPS);
    }

    bool operator != (const Triangle<T>& other) const noexcept {
        return !(*this == other);
    }

    friend std::ostream& operator << (std::ostream& os, const Triangle<T>& triangle) noexcept {
        triangle.print(os);
        return os;
    }

    friend std::istream& operator >> (std::istream& is, Triangle<T>& triangle) {
        is >> triangle.p1 >> triangle.p2 >> triangle.p3;
        triangle.throw_if_invalid();
        return is;
    }
};
