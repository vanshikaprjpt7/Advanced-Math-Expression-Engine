#ifndef SIMPLIFIER_H
#define SIMPLIFIER_H

#include <iostream>
#include <string>
#include "expression_tree.h"

using namespace std;

class Simplifier
{
public:
    bool isZero(string token);
    bool isOne(string token);

    Node* simplifyTree(Node *root);
};

#endif
