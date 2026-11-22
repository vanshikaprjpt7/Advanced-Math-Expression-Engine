
#include <iostream>
#include "tokenizer.h"

using namespace std;

int main()
{
    Tokenizer tokenizer;

    string expression;

    string tokens[100];

    int tokenCount = 0;

    cout << "Enter expression: ";

    getline(cin, expression);

    tokenizer.tokenize(expression, tokens, tokenCount);

    cout << "\nTokens:\n";

    for(int i = 0; i < tokenCount; i++)
    {
        cout << tokens[i] << endl;
    }

    return 0;
}
