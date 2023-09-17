#include <iostream>
using namespace std;

int main() {
    string str;
    getline(cin, str);
    if (str.empty()) {
        cerr << "Error: String is empty!" << endl;
        return 1;
    }
    int counter = 0;
    for (char x : str) {
        if (x != 32 && (x < 97 || x > 122)) {
            cerr << "Error: Invalid input!" << endl;
            return 2;
        }
        switch (x) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'y':
                ++counter;
                break;
        }
    }
    cout << "Answer: " << counter << endl;
}
