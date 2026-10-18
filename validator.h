#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <string>
using namespace std;
class Validator{
    public:
       bool validateExpression(const string tokens[], int tokenCount);
       bool checkParentheses(const string tokens[], int tokenCount);
       bool isOperator(const string & token);
       bool isNumber(const string& token);
       bool isVariable(const string &token);
       bool isOperand(const string &token);
       bool checkTokenSequence(const string tokens[], int tokenCount);


};
#endif