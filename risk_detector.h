
#ifndef RISK_DETECTOR_H
#define RISK_DETECTOR_H

#include <iostream>
#include <string>
using namespace std;

class RiskDetector
{
public:
    bool isZeroNumber(string token);
    bool detectDivisionByZero(string tokens[], int tokenCount);
};

#endif
