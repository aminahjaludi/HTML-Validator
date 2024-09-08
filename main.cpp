#include <iostream>
#include "HTMLChecker.h"
using namespace std;


int main() {
    string file_path = "tests/missing_opening_tag.html";
    HTMLChecker validator = HTMLChecker();
    validator.load(file_path);

    if (validator.isValid()) {
        cout << file_path << " is valid!" << endl;
    } else {
        cout << file_path << " is not valid!" << endl;
    }

    return 0;
}