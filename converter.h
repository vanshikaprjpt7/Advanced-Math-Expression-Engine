#ifndef CONVERTER_H
#define CONVERTER_H
#include <iostream>
#include <string>
using namespace std;
class Converter
{
public:
    bool isOperator(string token);
    int precedence(string op);
    int infixToPostfix(string tokens[], int n, string postfix[]);
    int infixToPrefix(string tokens[], int n, string prefix[]);
};
#endif
