include <iostream>
#include "expression_tree.h"
#include "repeated_detector.h"

using namespace std;

int main()
{
    RepeatedDetector detector;

    // Test 1: (A+B)*(A+B)
    cout << "\nTest 1: (A+B)*(A+B)" << endl;

    Node *root1 = buildExpressionTree("A B + A B + *");

    if(!detector.detectRepeatedSubexpressions(root1))
    {
        cout << "No repeated subexpression found." << endl;
    }

    deleteTree(root1);

    // Test 2: (X*Y)+(X*Y)
    cout << "\nTest 2: (X*Y)+(X*Y)" << endl;

    Node *root2 = buildExpressionTree("X Y * X Y * +");

    if(!detector.detectRepeatedSubexpressions(root2))
    {
        cout << "No repeated subexpression found." << endl;
    }

    deleteTree(root2);

    // Test 3: (A+B)*(C+D)
    cout << "\nTest 3: (A+B)*(C+D)" << endl;

    Node *root3 = buildExpressionTree("A B + C D + *");

    if(!detector.detectRepeatedSubexpressions(root3))
    {
        cout << "No repeated subexpression found." << endl;
    }

    deleteTree(root3);

    return 0;
}
