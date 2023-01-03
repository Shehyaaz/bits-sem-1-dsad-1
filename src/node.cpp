// Common node for Queue List and Sorted List
#include "node.hpp"

Node::Node(){
  // default constructor
  this->data = 0;
  this->next = nullptr;
}

Node::Node(const int data){
  // parameterised constructor
  this->data = data;
  this->next = nullptr;
}

Node::~Node(){
  // destructor
  delete next; // will delete the next element of the list recursively
}