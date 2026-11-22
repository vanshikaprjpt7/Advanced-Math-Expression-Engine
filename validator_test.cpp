
#include <iostream>
#include "tokenizer.h"
#include "validator.h"

using namespace std;

int main()
{
    Tokenizer tokenizer;
    Validator validator;

    string expression;
    string tokens[100];

    int tokenCount = 0;

    cout << "Enter expression: ";
    getline(cin, expression);

    tokenizer.tokenize(expression, tokens, tokenCount);

    cout << "\nValidation Result: ";

    if(validator.validateExpression(tokens, tokenCount))
    {
        cout << "Valid Expression";
    }

    else
    {
        cout << "Invalid Expression";
    }

    cout << endl;

    return 0;
}
