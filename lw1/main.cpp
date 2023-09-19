#include <iostream>
#include <string>
#include "vowels_count.h"

using namespace std;

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    int ans = vowels_count(str);
    if (ans == -1) {
        cout << endl;
        cerr << "Error: String is empty!" << endl;
        return 1;
    } else if (ans == -2) {
        cerr << "Error: Invalid input!" << endl;
        return 2;
    }
    cout << "Answer: " << ans << endl;
}
