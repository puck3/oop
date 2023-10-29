#pragma once
#include "figure.hpp"
#include "point.hpp"

template <std::floating_point T>
class Square final : public Figure<T> {
private:
    size_t size{4};
    Point<T> points[4];

protected:
    virtual void throw_if_invalid() const override {
        if (points[0] == points[2] || points[1] == points[3]) {
            throw std::invalid_argument("Figure is not square");
        }
        T side = seg_length(points[0], points[1]);
        for (size_t i{1}; i < size; ++i) {
            if (fabs(seg_length(points[i], points[(i + 1) % size]) - side) > EPS) {
                throw std::invalid_argument("Sides must be equal");
            }
        }
        if (fabs(seg_length(points[0], points[2]) * seg_length(points[0], points[2]) - 2 * side * side) > EPS) {
            if (points[0] == points[2] || points[1] == points[3]) {
                throw std::invalid_argument("Figure is not square");
            }
        }
    }

public:
    Square() noexcept = default;

    Square(Point<T>& p1, Point<T>& p2, Point<T>& p3, Point<T>& p4) {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
        this->throw_if_invalid();
    }

    ~Square() noexcept = default;

    virtual T area() const noexcept override {
        T s = seg_length(points[0], points[1]);
        return s * s;
    }

    virtual Point<T> center() const noexcept override {
        T x{0}, y{0};
        for (size_t i{0}; i < size; ++i) {
            x += points[i].get_x();
            y += points[i].get_y();
        }
        x /= size;
        y /= size;
        return Point<T>(x, y);
    }

    virtual void print(std::ostream& os) const noexcept override {
        os << "Vertices coordinates:" << std::endl;
        for (size_t i{0}; i < size; ++i) {
            os << points[i] << " ";
        }
        os << std::endl;
    }

    explicit virtual operator double() const noexcept override {
        return this->area();
    }

    bool operator == (const Square<T>& other) const noexcept {
        return (fabs(this->area() - other.area()) < EPS);
    }

    bool operator != (const Square<T>& other) const noexcept {
        return !(*this == other);
    }

    friend std::ostream& operator << (std::ostream& os, const Square<T>& square) noexcept {
        square.print(os);
        return os;
    }

    friend std::istream& operator >> (std::istream& is, Square<T>& square) {
        for (size_t i{0}; i < square.size; ++i) {
            is >> square.points[i];
        }
        square.throw_if_invalid();
        return is;
    }
};
