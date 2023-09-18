#include <iostream>
#include <gtest/gtest.h>
using namespace std;

int vowels_count(string str) {
    if (str.empty()) {
        cerr << "Error: String is empty!" << endl;
        exit(1);
    }
    int counter = 0;
    for (char x : str) {
        if (x != 32 && (x < 97 || x > 122)) {
            cerr << "Error: Invalid input!" << endl;
            exit(2);
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

TEST(vowels_count, basic_test) {
    ASSERT_TRUE(vowels_count(" ") == 0);
    ASSERT_TRUE(vowels_count("zxc") == 0);
    ASSERT_TRUE(vowels_count("queasy") == 4);
    ASSERT_TRUE(vowels_count("qwe asd   yui") == 5);
}

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    int ans = vowels_count(str);
    cout << "Answer: " << ans << endl;
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
