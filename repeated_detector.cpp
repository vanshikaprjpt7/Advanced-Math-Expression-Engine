#include <iostream>
#include <string>
#include "repeated_detector.h"

using namespace std;

// Creates a unique signature for every subtree
string RepeatedDetector::buildSignature(Node *root)
{
    if(root == nullptr)
    {
        return "";
    }

    if(root->left == nullptr && root->right == nullptr)
    {
        return root->data;
    }

    return "(" + buildSignature(root->left) +
           root->data +
           buildSignature(root->right) + ")";
}

// Counts occurrences throughout the given tree
int RepeatedDetector::countOccurrences(Node *root, string signature)
{
    if(root == nullptr)
    {
        return 0;
    }

    int count = 0;

    if(root->left != nullptr || root->right != nullptr)
    {
        if(buildSignature(root) == signature)
        {
            count++;
        }
    }

    count += countOccurrences(root->left, signature);
    count += countOccurrences(root->right, signature);

    return count;
}

// Finds the first occurrence of a signature
Node* findFirstOccurrence(
    Node *root, string signature,
    RepeatedDetector &detector)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    if(root->left != nullptr || root->right != nullptr)
    {
        if(detector.buildSignature(root) == signature)
        {
            return root;
        }
    }

    Node *leftResult =
        findFirstOccurrence(root->left, signature, detector);

    if(leftResult != nullptr)
    {
        return leftResult;
    }

    return findFirstOccurrence(root->right, signature, detector);
}

// Checks subtrees while keeping the original tree available
bool checkRepeated(
    Node *current, Node *wholeTree,
    RepeatedDetector &detector)
{
    if(current == nullptr)
    {
        return false;
    }

    bool found = false;

    if(current->left != nullptr || current->right != nullptr)
    {
        string signature = detector.buildSignature(current);

        // IMPORTANT: Search the entire original tree
        int occurrences =
            detector.countOccurrences(wholeTree, signature);

        if(occurrences > 1)
        {
            Node *first =
                findFirstOccurrence(wholeTree, signature, detector);

            // Print each repeated expression only once
            if(first == current)
            {
                cout << "Repeated subexpression detected: "
                     << signature << endl;
            }

            found = true;
        }
    }

    bool leftFound =
        checkRepeated(current->left, wholeTree, detector);

    bool rightFound =
        checkRepeated(current->right, wholeTree, detector);

    return found || leftFound || rightFound;
}

// Main detection function
bool RepeatedDetector::detectRepeatedSubexpressions(Node *root)
{
    if(root == nullptr)
    {
        return false;
    }

    return checkRepeated(root, root, *this);
}
