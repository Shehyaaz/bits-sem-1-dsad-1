// Queue List
#include "node.hpp"
#include <climits>

class QList {
  public:
    // data members
    Node* front; // front reference
    Node* rear; // rear reference
    int size; // size of queue
  
    // operations
    QList(); // default constructor
    QList(int* inputList, int inputSize); // constructor
    ~QList(); // destructor
    bool isEmpty();
    void enqueue(const int data);
    int dequeue();
    bool search(const int key);
    int getSize();
    Node* getFront();
    Node* getRear();
    void displayQueue();
};