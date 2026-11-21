#include <iostream>
#include <string>
#include "risk_detector.h"

using namespace std;

int main()
{
    RiskDetector detector;

    string test1[] = {"10", "/", "0"};
    string test2[] = {"A", "/", "0"};
    string test3[] = {"10", "/", "2"};
    string test4[] = {"A", "+", "B"};
    string test5[] = {"10", "/", "(", "0", ")"};
    string test6[] = {"10", "/", "0.0"};

    cout << "Test 1: ";
    cout << detector.detectDivisionByZero(test1, 3) << endl;

    cout << "Test 2: ";
    cout << detector.detectDivisionByZero(test2, 3) << endl;

    cout << "Test 3: ";
    cout << detector.detectDivisionByZero(test3, 3) << endl;

    cout << "Test 4: ";
    cout << detector.detectDivisionByZero(test4, 3) << endl;

    cout << "Test 5: ";
    cout << detector.detectDivisionByZero(test5, 5) << endl;

    cout << "Test 6: ";
    cout << detector.detectDivisionByZero(test6, 3) << endl;

    return 0;
}
