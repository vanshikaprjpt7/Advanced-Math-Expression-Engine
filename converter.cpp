#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include "converter.h"
using namespace std;
int precedence(char ch){
    if(ch=='^')
        return 3;
    else if(ch=='*' || ch=='/')
        return 2;
    else if(ch=='+' || ch=='-')
        return 1;
    return 0;
}
string infixToPostfix(string infix){
    stack<char> st;
    string postfix="";
    for(int i=0;i<infix.length();i++){
        char ch=infix[i];
        if(ch==' ')
            continue;
        if(isalnum(ch)){
            postfix+=ch;
            postfix+=' ';
        }
        else if(ch=='('){
            st.push(ch);
        }
        else if(ch==')'){
            while(!st.empty() && st.top()!='('){
                postfix+=st.top();
                postfix+=' ';
                st.pop();
            }
            if(st.empty())
                return "Invalid expression";

            st.pop();
        }
        else if(ch=='+' || ch=='-' || ch=='*' ||
                ch=='/' || ch=='^'){

            while(!st.empty() && st.top()!='(' &&
                (precedence(st.top())>precedence(ch) ||
                (precedence(st.top())==precedence(ch) && ch!='^'))){

                postfix+=st.top();
                postfix+=' ';
                st.pop();
            }
            st.push(ch);
        }
        else{
            return "Invalid expression";
        }
    }
    while(!st.empty()){
        if(st.top()=='(')
            return "Invalid expression";

        postfix+=st.top();
        postfix+=' ';
        st.pop();
    }
    return postfix;
}
string infixToPrefix(string infix){
    string postfix=infixToPostfix(infix);
    if(postfix=="Invalid expression")
        return "Invalid expression";
    stack<string> st;
    for(int i=0;i<postfix.length();i++){
        char ch=postfix[i];
        if(ch==' ')
            continue;
        if(isalnum(ch)){
            st.push(string(1,ch));
        }
        else{
            if(st.size()<2)
                return "Invalid expression";
            string b=st.top();
            st.pop();
            string a=st.top();
            st.pop();
            string temp=string(1,ch)+" "+a+" "+b;
            st.push(temp);
        }
    }
    if(st.size()!=1)
        return "Invalid expression";
    return st.top();
}
