#include <iostream>
#include "figure.hpp"

class FiguresArray {
private:
    size_t size;
    size_t capacity;
    Figure** data;

public:
    FiguresArray() noexcept;
    FiguresArray(size_t);
    FiguresArray(const FiguresArray&);
    FiguresArray(FiguresArray&&) noexcept;
    virtual ~FiguresArray() noexcept;

    FiguresArray& operator=(const FiguresArray&);
    FiguresArray& operator=(FiguresArray&&) noexcept;

    size_t length();
    void push_back(Figure*);
    Figure* pop_back();
    void erase(size_t);
    Figure* operator[] (size_t);

    friend std::ostream& operator<< (std::ostream&, const FiguresArray&) noexcept;
    double area() const noexcept;
};
