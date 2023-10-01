#include <iostream>
#include "twelve.hpp"

using namespace std;

int main() {
    try {
        Twelve A(7, '3');
        Twelve B(2, 'B');
        Twelve C{'1', 'B'};
        Twelve D("023A");
        Twelve E(B);
        Twelve F(move(E));
        E = D;
        cout << "B = " << B << endl;
        cout << "C = " << C << endl;
        cout << "B + C = " << B + C << endl;
        cout << "B - C = " << B - C << endl;
        B += C;
        cout << "B += C: " << B << endl;
        B -= C;
        cout << "(B + C) -= C: " << B << endl;
        B -= C;
        cout << "B -= C: " << B << endl;


    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }



}