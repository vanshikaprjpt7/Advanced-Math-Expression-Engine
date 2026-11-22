#ifndef REPEATED_DETECTOR_H
#define REPEATED_DETECTOR_H

#include <iostream>
#include <string>
#include "expression_tree.h"

using namespace std;

class RepeatedDetector
{
public:
    string buildSignature(Node *root);
    int countOccurrences(Node *root, string signature);
    bool detectRepeatedSubexpressions(Node *root);
};

#endif
