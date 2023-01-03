// Common node for Queue List and Sorted List
#ifndef NODE // guard wrapper
#define NODE

#include <iostream>
using namespace std;

class Node {
  public:
    // data members
    int data;
    Node* next;
    // operations
    Node(); // default constructor
    Node(const int data); // constructor
    ~Node(); // destructor
};
#endif