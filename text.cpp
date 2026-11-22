#include <iostream>
#include <string>
#include "texting.h"
#include "tokenizer.h"
#include "validator.h"
#include "converter.h"
#include "evaluator.h"
#include "expression_tree.h"
#include "risk_detector.h"
#include "simplifier.h"
#include "repeated_detector.h"

using namespace std;

static int passed = 0;
static int failed = 0;

void check(const string& name, bool result)
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

// Joins tokens into one space-separated string
static string joinTokens(const string tokens[], int count)
{
    string result = "";

    for(int i = 0; i < count; i++)
    {
        if(i > 0)
            result += " ";

        result += tokens[i];
    }

    return result;
}

// Splits an expression into tokens and returns the token count
static int tokenizeExpr(const string& expr, string tokens[])
{
    Tokenizer tokenizer;
    int count = 0;

    tokenizer.tokenize(expr, tokens, count);

    return count;
}

// Converts an infix expression to a postfix string
static string toPostfix(const string& expr)
{
    string tokens[100];
    string postfix[100];

    int n = tokenizeExpr(expr, tokens);

    Converter converter;
    int m = converter.infixToPostfix(tokens, n, postfix);

    return joinTokens(postfix, m);
}

// Converts an infix expression to a prefix string
static string toPrefix(const string& expr)
{
    string tokens[100];
    string prefix[100];

    int n = tokenizeExpr(expr, tokens);

    Converter converter;
    int m = converter.infixToPrefix(tokens, n, prefix);

    return joinTokens(prefix, m);
}

// Returns true if the validator accepts the expression
static bool isValid(const string& expr)
{
    string tokens[100];

    int n = tokenizeExpr(expr, tokens);

    Validator validator;
    return validator.validateExpression(tokens, n);
}

void runTests()
{
    passed = 0;
    failed = 0;

    cout << "\n===== TESTING STARTED =====\n\n";

    // ---------- Tokenizer ----------
    string tokens[100];

    int n = tokenizeExpr("2+3*(4-1)", tokens);
    check("Tokenizer count", n == 9);
    check("Tokenizer first tokens",
          tokens[0] == "2" && tokens[1] == "+" &&
          tokens[2] == "3" && tokens[3] == "*");

    n = tokenizeExpr("12+34", tokens);
    check("Multi-digit tokenization",
          n == 3 && tokens[0] == "12" &&
          tokens[1] == "+" && tokens[2] == "34");

    n = tokenizeExpr("2 + 3", tokens);
    check("Whitespace is skipped", n == 3);

    // ---------- Validator ----------
    check("Valid expression accepted", isValid("2+3*(4-1)"));
    check("Variable operand accepted", isValid("2+a"));
    check("Mismatched parentheses rejected", !isValid("(2+3"));
    check("Invalid character rejected", !isValid("2$3"));
    check("Missing operator rejected", !isValid("2 3"));
    check("Malformed number rejected", !isValid("1.2.3"));
    check("Empty brackets rejected", !isValid("()"));

    // ---------- Converter ----------
    check("Infix to postfix", toPostfix("2+3*4") == "2 3 4 * +");
    check("Parentheses to postfix", toPostfix("(2+3)*4") == "2 3 + 4 *");
    check("Right-associative exponent", toPostfix("2^3^2") == "2 3 2 ^ ^");
    check("Variable to postfix", toPostfix("2+a") == "2 a +");
    check("Infix to prefix", toPrefix("2+3*4") == "+ 2 * 3 4");

    // ---------- Evaluator ----------
    check("Postfix evaluation", evaluatePostfix("2 3 4 * + ") == 14);
    check("Prefix evaluation", evaluatePrefix("+ 2 * 3 4") == 14);
    check("Subtraction evaluation", evaluatePostfix("8 3 -") == 5);
    check("Division evaluation", evaluatePostfix("8 2 /") == 4);
    check("Exponent evaluation", evaluatePostfix("2 3 2 ^ ^") == 512);

    // ---------- Expression tree ----------
    Node *root = buildExpressionTree("2 3 4 * + ");
    check("Tree creation", root != NULL);

    if(root != NULL)
    {
        check("Tree evaluation", evaluateTree(root) == 14);
        deleteTree(root);
    }

    Node *root2 = buildExpressionTree("2 3 +");
    check("Two-operand tree evaluation",
          root2 != NULL && evaluateTree(root2) == 5);
    deleteTree(root2);

    check("Invalid postfix gives no tree",
          buildExpressionTree("2 +") == NULL);

    // ---------- Risk detector ----------
    RiskDetector detector;

    string risk1[] = {"10", "/", "0"};
    string risk2[] = {"A", "/", "0"};
    string risk3[] = {"10", "/", "2"};
    string risk4[] = {"10", "/", "(", "0", ")"};

    check("Literal zero divisor detected",
          detector.detectDivisionByZero(risk1, 3));
    check("Variable dividend with zero detected",
          detector.detectDivisionByZero(risk2, 3));
    check("Normal division not flagged",
          !detector.detectDivisionByZero(risk3, 3));
    check("Parenthesized zero detected",
          detector.detectDivisionByZero(risk4, 5));

    // ---------- Simplifier ----------
    Simplifier simplifier;

    Node *s1 = simplifier.simplifyTree(buildExpressionTree("x 0 +"));
    check("Simplify x + 0", s1 != NULL && s1->data == "x");
    deleteTree(s1);

    Node *s2 = simplifier.simplifyTree(buildExpressionTree("x 1 *"));
    check("Simplify x * 1", s2 != NULL && s2->data == "x");
    deleteTree(s2);

    Node *s3 = simplifier.simplifyTree(buildExpressionTree("x 0 *"));
    check("Simplify x * 0", s3 != NULL && s3->data == "0");
    deleteTree(s3);

    // ---------- Repeated detector ----------
    RepeatedDetector repeatedDetector;

    Node *rep1 = buildExpressionTree("A B + A B + *");
    check("Repeated (A+B)*(A+B) detected",
          repeatedDetector.detectRepeatedSubexpressions(rep1));
    deleteTree(rep1);

    Node *rep2 = buildExpressionTree("X Y * X Y * +");
    check("Repeated (X*Y)+(X*Y) detected",
          repeatedDetector.detectRepeatedSubexpressions(rep2));
    deleteTree(rep2);

    Node *rep3 = buildExpressionTree("A B + C D + *");
    check("No repeat in (A+B)*(C+D)",
          !repeatedDetector.detectRepeatedSubexpressions(rep3));
    deleteTree(rep3);

    // ---------- Integration ----------
    Node *pipe = buildExpressionTree(toPostfix("(2+3)*4"));
    check("Pipeline: (2+3)*4 evaluates to 20",
          pipe != NULL && evaluateTree(pipe) == 20);
    deleteTree(pipe);

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
