// Sorted List
#include "node.hpp"
#include <climits>

class SortedList {
  public:
    // data members
    Node* head; // list head reference
    int size; // size of list
  
    // operations
    SortedList(); // default constructor
    SortedList(int* inputList, int inputSize); // constructor
    ~SortedList(); // destructor
    bool isEmpty();
    void insert(const int data);
    int remove(const int data);
    bool search(const int key);
    int getSize();
    Node* getHead();
    void displayList();
};