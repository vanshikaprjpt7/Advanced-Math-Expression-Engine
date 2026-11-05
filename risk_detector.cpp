
#include <iostream>
#include <string>
#include "risk_detector.h"

using namespace std;

// Checks whether a token represents zero
bool RiskDetector::isZeroNumber(string token)
{
    bool hasDigit = false;

    for(int i = 0; i < token.length(); i++)
    {
        if(token[i] >= '0' && token[i] <= '9')
        {
            hasDigit = true;

            if(token[i] != '0')
            {
                return false;
            }
        }
        else if(token[i] != '.')
        {
            return false;
        }
    }

    return hasDigit;
}

// Detects direct division by zero
bool RiskDetector::detectDivisionByZero(
    string tokens[], int tokenCount)
{
    for(int i = 0; i < tokenCount; i++)
    {
        if(tokens[i] == "/")
        {
            // Case 1: A / 0
            if(i + 1 < tokenCount &&
               isZeroNumber(tokens[i + 1]))
            {
                return true;
            }

            // Case 2: A / ( 0 )
            if(i + 3 < tokenCount &&
               tokens[i + 1] == "(" &&
               isZeroNumber(tokens[i + 2]) &&
               tokens[i + 3] == ")")
            {
                return true;
            }
        }
    }

    return false;
}
