#include <iostream>
#include <string>
#include <cstdlib>
#include "simplifier.h"

using namespace std;

// Checks whether a token represents zero
bool Simplifier::isZero(string token)
{
    if(token.empty())
    {
        return false;
    }

    char *end;
    double value = strtod(token.c_str(), &end);

    return (*end == '\0' && value == 0);
}

// Checks whether a token represents one
bool Simplifier::isOne(string token)
{
    if(token.empty())
    {
        return false;
    }

    char *end;
    double value = strtod(token.c_str(), &end);

    return (*end == '\0' && value == 1);
}

// Simplifies the expression tree
Node* Simplifier::simplifyTree(Node *root)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    // Simplify left and right subtrees first
    root->left = simplifyTree(root->left);
    root->right = simplifyTree(root->right);

    // A + 0 = A
    if(root->data == "+" && isZero(root->right->data))
    {
        Node *temp = root->left;

        deleteTree(root->right);
        delete root;

        return temp;
    }

    // 0 + A = A
    if(root->data == "+" && isZero(root->left->data))
    {
        Node *temp = root->right;

        deleteTree(root->left);
        delete root;

        return temp;
    }

    // A - 0 = A
    if(root->data == "-" && isZero(root->right->data))
    {
        Node *temp = root->left;

        deleteTree(root->right);
        delete root;

        return temp;
    }

    // A * 1 = A
    if(root->data == "*" && isOne(root->right->data))
    {
        Node *temp = root->left;

        deleteTree(root->right);
        delete root;

        return temp;
    }

    // 1 * A = A
    if(root->data == "*" && isOne(root->left->data))
    {
        Node *temp = root->right;

        deleteTree(root->left);
        delete root;

        return temp;
    }

    // A * 0 = 0
    // 0 * A = 0
    if(root->data == "*" &&
       (isZero(root->left->data) ||
        isZero(root->right->data)))
    {
        deleteTree(root->left);
        deleteTree(root->right);

        root->left = nullptr;
        root->right = nullptr;
        root->data = "0";

        return root;
    }

    // A / 1 = A
    if(root->data == "/" && isOne(root->right->data))
    {
        Node *temp = root->left;

        deleteTree(root->right);
        delete root;

        return temp;
    }

    return root;
}
