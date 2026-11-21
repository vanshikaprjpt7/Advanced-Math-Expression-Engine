#include "converter.h"
#include <stack>
using namespace std;
bool Converter::isOperator(string token)
{
    if(token == "+" || token == "-" ||
       token == "*" || token == "/" ||
       token == "%" || token == "^")
    {
        return true;
    }
    return false;
}
int Converter::precedence(string op)
{
    if(op == "^")
    {
        return 3;
    }
    if(op == "*" || op == "/" || op == "%")
    {
        return 2;
    }
    if(op == "+" || op == "-")
    {
        return 1;
    }
    return 0;
}
int Converter::infixToPostfix(string tokens[], int n, string postfix[])
{
    stack<string> s;
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        string token = tokens[i];
        if(!isOperator(token) && token != "(" && token != ")")
        {
            postfix[j] = token;
            j++;
        }
        else if(token == "(")
        {
            s.push(token);
        }
        else if(token == ")")
        {
            while(!s.empty() && s.top() != "(")
            {
                postfix[j] = s.top();
                j++;
                s.pop();
            }

            if(!s.empty())
            {
                s.pop();
            }
        }
        else
        {
            while(!s.empty() &&
                  s.top() != "(" &&
                  (precedence(s.top()) > precedence(token) ||
                  (precedence(s.top()) == precedence(token) && token != "^")))
            {
                postfix[j] = s.top();
                j++;
                s.pop();
            }

            s.push(token);
        }
    }
    while(!s.empty())
    {
        postfix[j] = s.top();
        j++;
        s.pop();
    }
    return j;
}
int Converter::infixToPrefix(string tokens[], int n, string prefix[])
{
    string reversed[100];
    string temp[100];
    int j = 0;
    for(int i = 0; i < n; i++)
    {
        reversed[i] = tokens[n - i - 1];
        if(reversed[i] == "(")
        {
            reversed[i] = ")";
        }
        else if(reversed[i] == ")")
        {
            reversed[i] = "(";
        }
    }
    stack<string> s;
    for(int i = 0; i < n; i++)
    {
        string token = reversed[i];
        if(!isOperator(token) && token != "(" && token != ")")
        {
            temp[j] = token;
            j++;
        }
        else if(token == "(")
        {
            s.push(token);
        }
        else if(token == ")")
        {
            while(!s.empty() && s.top() != "(")
            {
                temp[j] = s.top();
                j++;
                s.pop();
            }
            if(!s.empty())
            {
                s.pop();
            }
        }
        else
        {
            while(!s.empty() &&
                  s.top() != "(" &&
                  (precedence(s.top()) > precedence(token) ||
                  (precedence(s.top()) == precedence(token) && token == "^")))
            {
                temp[j] = s.top();
                j++;
                s.pop();
            }
            s.push(token);
        }
    }
    while(!s.empty())
    {
        temp[j] = s.top();
        j++;
        s.pop();
    }
    for(int i = 0; i < j; i++)
    {
        prefix[i] = temp[j - i - 1];
    }

    return j;
}
