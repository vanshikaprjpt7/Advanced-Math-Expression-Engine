#include <iostream>
#include <string>
#include "converter.h"
#include "evaluator.h"
#include "expression_tree.h"
using namespace std;
int main()
{
    string infix,postfix,prefix;
    cout<<"Enter infix expression: ";
    getline(cin,infix);
    postfix=infixToPostfix(infix);
    prefix=infixToPrefix(infix);
    cout<<"\nPostfix: "<<postfix;
    cout<<"\nPrefix: "<<prefix;
    cout<<"\nPostfix Evaluation: "<<evaluatePostfix(postfix);
    cout<<"\nPrefix Evaluation: "<<evaluatePrefix(prefix);
    Node *root=buildExpressionTree(postfix);
    if(root==NULL)
    {
        cout<<"\nInvalid expression tree";
        return 0;
    }
    cout<<"\n\nPreorder: ";
    preorder(root);
    cout<<"\nInorder: ";
    inorder(root);
    cout<<"\nPostorder: ";
    postorder(root);
    cout<<"\nTree Evaluation: "<<evaluateTree(root);
    deleteTree(root);
    return 0;
}
