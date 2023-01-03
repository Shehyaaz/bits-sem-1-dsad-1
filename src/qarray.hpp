// Queue Array - Implement a circular queue using array
#include <iostream>
#include <climits>
using namespace std;

class QArray {
  public:
    // data members
    int* queue; // queue array
    int front; // front index
    int rear; // rear index
    int capacity; // capacity of queue
  
    // operations
    QArray(); // default constructor
    QArray(int* inputList, int inputSize); // constructor
    ~QArray(); // destructor
    bool isEmpty();
    bool isFull();
    void enqueue(const int data);
    int dequeue();
    bool search(const int key);
    int getSize();
    int getCapacity();
    int getFront();
    int getRear();
    void displayQueue();
};
