#include <string>
#include "vowels_count.h"

int vowels_count(std::string str) {
    if (str.empty()) {
        return -1;
    }
    int counter = 0;
    for (char x : str) {
        if (x != 32 && (x < 97 || x > 122)) {
            return -2;

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
    return counter;
}