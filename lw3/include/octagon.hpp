#include "figure.hpp"
#include "point.hpp"

class Octagon final : public Figure {
private:
    size_t size{8};
    Point points[8];

protected:
    virtual void throw_if_invalid() const override;

public:
    Octagon() noexcept = default;
    Octagon(Point&, Point&, Point&, Point&, Point&, Point&, Point&, Point&);
    Octagon(const Octagon&) noexcept;
    Octagon(const Octagon&&) noexcept;
    ~Octagon() noexcept = default;

    virtual double area() const noexcept override;
    virtual Point center() const noexcept override;
    virtual void print(std::ostream&) const noexcept override;
    explicit virtual operator double() const noexcept override;

    Octagon& operator= (const Octagon&) noexcept;
    Octagon& operator= (const Octagon&&) noexcept;
    bool operator == (const Octagon&) const noexcept;
    bool operator != (const Octagon&) const noexcept;

    friend std::ostream& operator << (std::ostream&, const Octagon&) noexcept;
    friend std::istream& operator >> (std::istream&, Octagon&);
};
