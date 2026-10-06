#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
using namespace std;

class Tokenizer{
  public: 
    void tokenize(const string & expression, string tokens[], int& tokenCount);
    bool isOperator(char ch);
    bool isParenthesis(char ch);
    bool isWhitespace(char ch);
};

#endif
