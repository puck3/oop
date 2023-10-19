#include <iostream>
#include "point.hpp"

using namespace std;

int main() {
    Point p1(1, 2);
    Point p2(2, 3);
    Point p3(3, 4);
    if (on_same_line(p1, p2, p3)) {
        cout << p1 << " " << p2 << " " << p3 << endl;
    }

}
