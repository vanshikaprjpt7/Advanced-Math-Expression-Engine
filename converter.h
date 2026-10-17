#ifndef CONVERTER_H
#define CONVERTER_H
#include <string>
using namespace std;
int precedence(char ch);
string infixToPostfix(string infix);
string infixToPrefix(string infix);
#endif
