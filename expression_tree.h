#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
#include <iostream>
#include <string>
using namespace std;
struct Node
{
    string data;
    Node *left;
    Node *right;
};
Node* buildExpressionTree(string postfix);
void preorder(Node *root);
void inorder(Node *root);
void postorder(Node *root);
double evaluateTree(Node *root);
void deleteTree(Node *root);
#endif
