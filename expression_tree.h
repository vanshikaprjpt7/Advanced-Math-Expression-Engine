#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
#include <iostream>
#include <string>
using namespace std;
struct Node
{
    char data;
    Node *left;
    Node *right;
};
Node* buildExpressionTree(string postfix);
void preorder(Node *root);
void inorder(Node *root);
void postorder(Node *root);
int evaluateTree(Node *root);
void deleteTree(Node *root);
#endif
