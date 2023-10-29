#include "figure.hpp"
#include "point.hpp"

class Square final : public Figure {
private:
    size_t size{4};
    Point points[4];

protected:
    virtual void throw_if_invalid() const override;

public:
    Square() noexcept = default;
    Square(Point&, Point&, Point&, Point&);
    Square(const Square&) noexcept;
    Square(Square&&) noexcept;
    ~Square() noexcept = default;

    virtual double area() const noexcept override;
    virtual Point center() const noexcept override;
    virtual void print(std::ostream&) const noexcept override;
    explicit virtual operator double() const noexcept override;

    Square& operator= (const Square&) noexcept;
    Square& operator= (Square&&) noexcept;
    bool operator == (const Square&) const noexcept;
    bool operator != (const Square&) const noexcept;

    friend std::ostream& operator << (std::ostream&, const Square&) noexcept;
    friend std::istream& operator >> (std::istream&, Square&);
};
