#include <memory>
#include <iostream>
#include "point.hpp"
#include "octagon.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "array.hpp"

using namespace std;

int main() {
    Array<std::shared_ptr<Figure<double>>> array;
    Array<std::shared_ptr<Figure<double>>> arr;
    Point<double> p1{-5, -1}, p2{-5, 2}, p3{-3, 6}, p4{2, 6}, p5{5, 4}, p6{4, -2}, p7{2, -3}, p8{-3, -3};
    Point<double> p9{0, 0}, p10{0, 3}, p11{3, 0}, p12{3, 3};
    Octagon<double> a{p1, p2, p3, p4, p5, p6, p7, p8};
    Octagon<double> b;
    Triangle<double> c{p9, p10, p11};
    Square<double> d{p9, p10, p12, p11};
    Triangle<double> e;
    Square<double> f(d);
    cout << f << endl;
    arr.push_back(make_shared<Octagon<double>>(a));
    arr.push_back(make_shared<Octagon<double>>(b));
    arr.push_back(make_shared<Triangle<double>>(c));
    arr.push_back(make_shared<Square<double>>(d));
    arr.push_back(make_shared<Triangle<double>>(e));
    arr.push_back(make_shared<Square<double>>(f));
    cout << "double(a) = " << double(a) << endl;
    cout << "a.area() = " << a.area() << endl;
    cout << arr << arr.area() << endl;
    arr.erase(2);
    cout << endl;
    cout << "Deleting..." << endl;
    arr.pop_back()->print(cout);
    Array<std::shared_ptr<Figure<double>>> arr2;
    arr2 = arr;
    Array<std::shared_ptr<Figure<double>>> arr3;
    arr3 = move(arr2);
    cout << endl;
    cout << arr3;
    cout << e;
    cin >> e;
    cout << e;
}
