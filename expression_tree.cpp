#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include "expression_tree.h"
using namespace std;
Node* buildExpressionTree(string postfix)
{
    stack<Node*> st;
    for(int i=0;i<postfix.length();i++)
    {
        char ch=postfix[i];
        if(ch==' ')
            continue;
        Node *temp=new Node;
        temp->data=ch;
        temp->left=NULL;
        temp->right=NULL;
        if(isdigit(ch))
        {
            st.push(temp);
        }
        else
        {
            if(st.size()<2)
            {
                cout<<"Invalid expression";
                delete temp;
                return NULL;
            }
            temp->right=st.top();
            st.pop();
            temp->left=st.top();
            st.pop();
            st.push(temp);
        }
    }
    if(st.size()!=1)
        return NULL;
    return st.top();
}
void preorder(Node *root)
{
    if(root==NULL)
        return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
void inorder(Node *root)
{
    if(root==NULL)
        return;
    if(root->left!=NULL)
        cout<<"(";
    inorder(root->left);
    cout<<root->data;
    inorder(root->right);
    if(root->right!=NULL)
        cout<<")";
}
void postorder(Node *root)
{
    if(root==NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
int evaluateTree(Node *root)
{
    if(root==NULL)
        return 0;
    if(isdigit(root->data))
        return root->data-'0';
    int a=evaluateTree(root->left);
    int b=evaluateTree(root->right);
    if(root->data=='+')
        return a+b;
    else if(root->data=='-')
        return a-b;
    else if(root->data=='*')
        return a*b;
    else if(root->data=='/')
    {
        if(b==0)
        {
            cout<<"Cannot divide by zero";
            return 0;
        }
        return a/b;
    }
    else if(root->data=='^')
        return pow(a,b);
    return 0;
}
void deleteTree(Node *root){
    if(root==NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
