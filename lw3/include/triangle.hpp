#include "figure.hpp"
#include "point.hpp"

class Triangle final : public Figure {
private:
    Point p1, p2, p3;

protected:
    virtual void throw_if_invalid() const override;

public:
    Triangle() noexcept = default;
    Triangle(Point&, Point&, Point&);
    Triangle(const Triangle&) noexcept;
    Triangle(const Triangle&&) noexcept;
    ~Triangle() noexcept = default;

    virtual double area() const noexcept override;
    virtual Point center() const noexcept override;
    virtual void print(std::ostream&) const noexcept override;

    explicit virtual operator double() const noexcept override;

    Triangle& operator= (const Triangle&) noexcept;
    Triangle& operator= (const Triangle&&) noexcept;
    bool operator == (const Triangle&) const noexcept;
    bool operator != (const Triangle&) const noexcept;

    friend std::ostream& operator << (std::ostream&, const Triangle&) noexcept;
    friend std::istream& operator >> (std::istream&, Triangle&);
};
