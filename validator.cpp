
#include "validator.h"
#include <cctype>
using namespace std;

bool Validator::isOperator(const string& token)
{
    return token == "+" || token == "-" ||
           token == "*" || token == "/" ||
           token == "%" || token == "^";
}

bool Validator::isNumber(const string& token)
{
    if(token.empty())
        return false;

    bool digitFound = false;
    bool decimalFound = false;

    for(int i = 0; i < token.length(); i++)
    {
        if(isdigit(static_cast<unsigned char>(token[i])))
            digitFound = true;
        else if(token[i] == '.' && !decimalFound)
            decimalFound = true;
        else
            return false;
    }

    return digitFound;
}

bool Validator::isVariable(const string& token)
{
    if(token.empty() ||
       !isalpha(static_cast<unsigned char>(token[0])))
        return false;

    for(int i = 1; i < token.length(); i++)
    {
        if(!isalnum(static_cast<unsigned char>(token[i])) &&
           token[i] != '_')
            return false;
    }

    return true;
}

bool Validator::isOperand(const string& token)
{
    return isNumber(token) || isVariable(token);
}

bool Validator::checkParentheses(
    const string tokens[], int tokenCount)
{
    int count = 0;

    for(int i = 0; i < tokenCount; i++)
    {
        if(tokens[i] == "(")
            count++;
        else if(tokens[i] == ")")
        {
            count--;

            if(count < 0)
                return false;
        }
    }

    return count == 0;
}

bool Validator::checkTokenSequence(
    const string tokens[], int tokenCount)
{
    if(tokenCount == 0)
        return false;

    bool expectOperand = true;

    for(int i = 0; i < tokenCount; i++)
    {
        string token = tokens[i];

        if(expectOperand)
        {
            if(token == "(")
                continue;

            if(isOperand(token))
                expectOperand = false;
            else
                return false;
        }
        else
        {
            if(isOperator(token))
                expectOperand = true;
            else if(token == ")")
                continue;
            else
                return false;
        }
    }

    return !expectOperand;
}

bool Validator::validateExpression(
    const string tokens[], int tokenCount)
{
    return checkParentheses(tokens, tokenCount) &&
           checkTokenSequence(tokens, tokenCount);
}