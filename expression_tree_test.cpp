#include <iostream>
#include <string>
#include "expression_tree.h"
using namespace std;
int main()
{
    Node *root;
    cout << "TEST 1: Basic Expression" << endl;
    root = buildExpressionTree("2 3 +");
    if(root != NULL)
    {
        cout << "Inorder: ";
        inorder(root);
        cout << "\nPreorder: ";
        preorder(root);
        cout << "\nPostorder: ";
        postorder(root);
        cout << "\nResult: " << evaluateTree(root) << endl;
        deleteTree(root);
    }
    cout << "\nTEST 2: Decimal Expression" << endl;
    root = buildExpressionTree("25.75 4.25 +");
    if(root != NULL)
    {
        cout << "Result: " << evaluateTree(root) << endl;
        deleteTree(root);
    }
    cout << "\nTEST 3: Variable Expression" << endl;
    root = buildExpressionTree("total value1 +");
    if(root != NULL)
    {
        cout << "Inorder: ";
        inorder(root);
        cout << "\nPreorder: ";
        preorder(root);
        cout << endl;
        deleteTree(root);
    }
    cout << "\nTEST 4: Complex Expression" << endl;
    root = buildExpressionTree("2 3 4 * +");
    if(root != NULL)
    {
        cout << "Result: " << evaluateTree(root) << endl;
        deleteTree(root);
    }
    return 0;
}
