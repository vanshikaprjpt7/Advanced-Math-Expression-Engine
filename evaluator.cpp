#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>
#include "evaluator.h"
using namespace std;
int calculate(int a,int b,char op){
    if(op=='+')
        return a+b;
    else if(op=='-')
        return a-b;
    else if(op=='*')
        return a*b;
    else if(op=='/'){
        if(b==0){
            cout<<"Division by zero not possible"<<endl;
            return 0;
        }
        return a/b;
    }
    else if(op=='^')
        return pow(a,b);
    return 0;
}
int evaluatePostfix(string postfix)
{
    stack<int> st;
    for(int i=0;i<postfix.length();i++)
    {
        char ch=postfix[i];
        if(ch==' ')
            continue;
        if(isdigit(ch))
        {
            st.push(ch-'0');
        }
        else
        {
            if(st.size()<2)
            {
                cout<<"Invalid postfix expression"<<endl;
                return 0;
            }
            int b=st.top();
            st.pop();
            int a=st.top();
            st.pop();
            int result=calculate(a,b,ch);
            st.push(result);
        }
    }
    if(st.size()!=1)
    {
        cout<<"Invalid postfix expression"<<endl;
        return 0;
    }
    return st.top();
}
int evaluatePrefix(string prefix)
{
    stack<int> st;
    for(int i=prefix.length()-1;i>=0;i--)
    {
        char ch=prefix[i];
        if(ch==' ')
            continue;
        if(isdigit(ch))
        {
            st.push(ch-'0');
        }
        else
        {
            if(st.size()<2)
            {
                cout<<"Invalid prefix expression"<<endl;
                return 0;
            }
            int a=st.top();
            st.pop();
            int b=st.top();
            st.pop();
            int result=calculate(a,b,ch);
            st.push(result);
        }
    }
    if(st.size()!=1)
    {
        cout<<"Invalid prefix expression"<<endl;
        return 0;
    }
    return st.top();
}
