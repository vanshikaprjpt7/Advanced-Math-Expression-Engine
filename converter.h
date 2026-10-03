#ifndef CONVERTER_H
#define CONVERTER_H

#include<string>
#include<vector>

using namespace std;

class Converter{
    public:
    bool isOperator(const string &token);
    int precedence(const string &op);
    bool isRightAssociative(const string &op);
    vector<string> infixToPostfix(vector<string> tokens);
    vector<string> infixToPrefix(vector<string> tokens);
};

#endif