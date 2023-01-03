// BST Node
#include "tnode.hpp"

TNode::TNode(){
  // default constructor
  this->key = 0;
  this->height = 0;
  this->left = nullptr;
  this->right = nullptr;
}

TNode::TNode(const int key){
  // parameterised constructor
  this->key = key;
  this->height = 0; // new node is initially added at leaf
  this->left = nullptr;
  this->right = nullptr;
}

TNode::~TNode(){
  // destructor
  delete left; // will delete left sub-tree of this node
  delete right; // will delete right sub-tree of this node
}