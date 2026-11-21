#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include "expression_tree.h"
using namespace std;
bool isTreeOperator(string token)
{
    return (token == "+" || token == "-" ||
            token == "*" || token == "/" ||
            token == "%" || token == "^");
}
bool isNumericToken(string token)
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
Node* buildExpressionTree(string postfix)
{
    stack<Node*> st;
    int i = 0;
    while(i < postfix.length())
    {
        if(isspace(static_cast<unsigned char>(postfix[i])))
        {
            i++;
            continue;
        }
        string token = "";
        while(i < postfix.length() &&
              !isspace(static_cast<unsigned char>(postfix[i])))
        {
            token += postfix[i];
            i++;
        }
        Node *temp = new Node;
        temp->data = token;
        temp->left = NULL;
        temp->right = NULL;
        if(!isTreeOperator(token))
        {
            st.push(temp);
        }
        else
        {
            if(st.size() < 2)
            {
                delete temp;

                while(!st.empty())
                {
                    deleteTree(st.top());
                    st.pop();
                }

                return NULL;
            }
            temp->right = st.top();
            st.pop();
            temp->left = st.top();
            st.pop();
            st.push(temp);
        }
    }
    if(st.size() != 1)
    {
        while(!st.empty())
        {
            deleteTree(st.top());
            st.pop();
        }
        return NULL;
    }
    return st.top();
}
void preorder(Node *root)
{
    if(root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node *root)
{
    if(root == NULL)
        return;
    if(root->left != NULL)
        cout << "(";
    inorder(root->left);
    cout << root->data;
    inorder(root->right);
    if(root->right != NULL)
        cout << ")";
}
void postorder(Node *root)
{
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
double evaluateTree(Node *root)
{
    if(root == NULL)
        return 0;
    if(isNumericToken(root->data))
        return atof(root->data.c_str());
    if(!isTreeOperator(root->data))
    {
        cout << "\nCannot evaluate expression containing variables.";
        return 0;
    }
    double a = evaluateTree(root->left);
    double b = evaluateTree(root->right);
    if(root->data == "+")
        return a + b;

    else if(root->data == "-")
        return a - b;

    else if(root->data == "*")
        return a * b;

    else if(root->data == "/")
    {
        if(b == 0)
        {
            cout << "\nCannot divide by zero.";
            return 0;
        }

        return a / b;
    }
    else if(root->data == "%")
    {
        if(b == 0)
        {
            cout << "\nCannot perform modulo by zero.";
            return 0;
        }
        return fmod(a, b);
    }
    else if(root->data == "^")
        return pow(a, b);

    return 0;
}
void deleteTree(Node *root)
{
    if(root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
