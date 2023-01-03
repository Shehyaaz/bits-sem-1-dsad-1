// BST Node
#ifndef TNODE // guard wrapper
#define TNODE

#include <iostream>
using namespace std;

class TNode {
  public:
    // data members
    int key;
    int height; // height of a node: no. of edges on the longest path from the node to a leaf
    TNode* left;
    TNode* right;
    // operations
    TNode(); // default constructor
    TNode(const int key); // constructor
    ~TNode(); // destructor
};
#endif