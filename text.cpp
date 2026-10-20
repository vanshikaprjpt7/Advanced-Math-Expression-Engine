#include <iostream>
#include <string>
#include "testing.h"
#include "converter.h"
#include "evaluator.h"
#include "tokenizer.h"
#include "expression_tree.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(string name, bool result)
{
    if(result)
    {
        cout << "[PASS] " << name << endl;
        passed++;
    }
    else
    {
        cout << "[FAIL] " << name << endl;
        failed++;
    }
}

void runTests()
{
    passed = 0;
    failed = 0;

    cout << "\n===== TESTING STARTED =====\n\n";

    check("Valid Expression",
          infixToPostfix("2+3*4") == "2 3 4 * + ");

    check("Undefined Variable",
          infixToPostfix("2+a") == "2 a + ");

    check("Divide By Zero",
          evaluatePostfix("4 0 /") == 0);

    check("Mismatched Parentheses",
          infixToPostfix("(2+3") == "Invalid expression");

    check("Invalid Operator",
          infixToPostfix("2$3") == "Invalid expression");

    check("Infix to Postfix",
          infixToPostfix("2+3*4") == "2 3 4 * + ");

    check("Infix to Prefix",
          infixToPrefix("2+3*4") == "+ 2 * 3 4");

    check("Postfix Evaluation",
          evaluatePostfix("2 3 4 * + ") == 14);

    check("Prefix Evaluation",
          evaluatePrefix("+ 2 * 3 4") == 14);

    check("Parentheses Handling",
          infixToPostfix("(2+3)*4") == "2 3 + 4 * ");

    check("Exponent Conversion",
          infixToPostfix("2^3^2") == "2 3 2 ^ ^ ");

    check("Exponent Evaluation",
          evaluatePostfix("2 3 2 ^ ^ ") == 512);

    check("Invalid Postfix",
          evaluatePostfix("2 +") == 0);

    check("Subtraction Evaluation",
          evaluatePostfix("8 3 -") == 5);

    check("Division Evaluation",
          evaluatePostfix("8 2 /") == 4);

    check("Invalid Prefix",
          evaluatePrefix("+ 2") == 0);

    Tokenizer tokenizer;
    string tokens[100];
    int tokenCount = 0;

    tokenizer.tokenize("2+3*(4-1)", tokens, tokenCount);

    check("Tokenizer",
          tokenCount == 9 &&
          tokens[0] == "2" &&
          tokens[1] == "+" &&
          tokens[2] == "3" &&
          tokens[3] == "*");

    tokenizer.tokenize("12+34", tokens, tokenCount);

    check("Multiple Digit Tokenization",
          tokenCount == 3 &&
          tokens[0] == "12" &&
          tokens[1] == "+" &&
          tokens[2] == "34");

    check("Whitespace Handling",
          infixToPostfix("2 + 3") == "2 3 + ");

    Node *root = buildExpressionTree("2 3 4 * + ");

    check("Expression Tree Creation",
          root != NULL);

    if(root != NULL)
    {
        check("Expression Tree Evaluation",
              evaluateTree(root) == 14);

        deleteTree(root);
    }

    Node *testRoot = buildExpressionTree("2 3 +");

    check("Additional Expression Tree Creation",
          testRoot != NULL);

    deleteTree(testRoot);

    cout << "\n===== TEST SUMMARY =====\n";
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "Total: " << passed + failed << endl;
}

int main()
{
    runTests();
    return 0;
}
