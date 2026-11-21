#include <iostream>
#include <string>

#include "expression_tree.h"
#include "simplifier.h"

using namespace std;

int main()
{
    Simplifier simplifier;

    string postfix;

    cout << "Enter postfix expression: ";
    getline(cin, postfix);

    Node *root = buildExpressionTree(postfix);

    if(root == nullptr)
    {
        cout << "Invalid expression tree." << endl;
        return 0;
    }

    cout << "\nOriginal Expression: ";
    inorder(root);
    cout << endl;

    root = simplifier.simplifyTree(root);

    cout << "\nSimplified Expression: ";
    inorder(root);
    cout << endl;

    cout << "\nSimplification completed!" << endl;

    deleteTree(root);

    return 0;
}
