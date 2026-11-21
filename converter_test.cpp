#include <iostream>
#include "tokenizer.h"
#include "validator.h"
#include "converter.h"
using namespace std;
int main()
{
    Tokenizer tokenizer;
    Validator validator;
    Converter converter;
    string expression;
    string tokens[100];
    string postfix[100];
    string prefix[100];
    int tokenCount = 0;
    int postfixCount = 0;
    int prefixCount = 0;
    cout << "Enter mathematical expression: ";
    getline(cin, expression);
    tokenizer.tokenize(expression, tokens, tokenCount);
    if(!validator.validateExpression(tokens, tokenCount))
    {
        cout << "Invalid Expression!" << endl;
        return 0;
    }
    postfixCount = converter.infixToPostfix(tokens, tokenCount, postfix);
    prefixCount = converter.infixToPrefix(tokens, tokenCount, prefix);
    cout << "\nInfix Expression: " << expression;
    cout << "\n\nPostfix Expression: ";
    for(int i = 0; i < postfixCount; i++)
    {
        cout << postfix[i] << " ";
    }
    cout << "\n\nPrefix Expression: ";
    for(int i = 0; i < prefixCount; i++)
    {
        cout << prefix[i] << " ";
    }
    cout << endl;
    return 0;
}
