#include <iostream>
#include "point.hpp"
#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "figures_array.hpp"

using namespace std;

int main() {
    FiguresArray arr;
    Point p1{-5, -1}, p2{-5, 2}, p3{-3, 6}, p4{2, 6}, p5{5, 4}, p6{4, -2}, p7{2, -3}, p8{-3, -3};
    Point p9{0, 0}, p10{0, 3}, p11{3, 0}, p12{3, 3};
    Octagon a{p1, p2, p3, p4, p5, p6, p7, p8};
    Octagon b;
    Triangle c{p9, p10, p11};
    Square d{p9, p10, p12, p11};
    Triangle e;
    Square f;
    arr.push_back(&a);
    arr.push_back(&b);
    arr.push_back(&c);
    arr.push_back(&d);
    arr.push_back(&e);
    arr.push_back(&f);
    cout << "double(a) = " << double(a) << endl;
    cout << "a.area() = " << a.area() << endl;
    cout << arr << arr.area() << endl;
    arr.erase(2);
    cout << endl;
    cout << "Deleting..." << endl;
    arr.pop_back()->print(cout);
    FiguresArray arr2;
    arr2 = arr;
    FiguresArray arr3;
    arr3 = move(arr2);
    cout << endl;
    cout << arr3;
}
