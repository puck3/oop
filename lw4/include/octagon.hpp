#pragma once
#include "figure.hpp"
#include "point.hpp"

template <std::floating_point T>
class Octagon final : public Figure<T> {
private:
    size_t size{8};
    Point<T> points[8];

protected:
    virtual void throw_if_invalid() const override {
        if (on_same_line(points[0], points[1], points[2])) {
            throw std::invalid_argument("3 points lay on the same line");
        }
        int sign = cross_product_sign(points[0], points[1], points[2]);
        for (size_t i{1}; i < size; ++i) {
            if (on_same_line(points[0], points[1], points[2])) {
                throw std::invalid_argument("3 points lay on the same line");
            }
            if (cross_product_sign(points[i], points[(i + 1) % size], points[(i + 2) % size]) != sign) {
                throw std::invalid_argument("Figure is not convex");
            }
        }
    }

public:
    Octagon() noexcept = default;

    Octagon(Point<T>& p1, Point<T>& p2, Point<T>& p3, Point<T>& p4, Point<T>& p5, Point<T>& p6, Point<T>& p7, Point<T>& p8) {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
        points[3] = p4;
        points[4] = p5;
        points[5] = p6;
        points[6] = p7;
        points[7] = p8;
        this->throw_if_invalid();
    }

    ~Octagon() noexcept = default;

    virtual T area() const noexcept override {
        T s{0};
        for (size_t i{0}; i < size; ++i) {
            s += points[i].get_x() * (points[(i + 1) % size].get_y() - points[(size + i - 1) % size].get_y());
        }
        s /= 2;
        return fabs(s);
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

    bool operator == (const Octagon<T>& other) const noexcept {
        return (fabs(this->area() - other.area()) < EPS);
    }

    bool operator != (const Octagon<T>& other) const noexcept {
        return !(*this == other);
    }

    friend std::ostream& operator << (std::ostream& os, const Octagon<T>& octagon) noexcept {
        octagon.print(os);
        return os;
    }

    friend std::istream& operator >> (std::istream& is, Octagon<T>& octagon) {
        for (size_t i{0}; i < octagon.size; ++i) {
            is >> octagon.points[i];
        }
        octagon.throw_if_invalid();
        return is;
    }
};
