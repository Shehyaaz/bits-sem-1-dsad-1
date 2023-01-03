// Queue Array - Implement a circular queue using array
#include "qarray.hpp"

QArray::QArray(){
  // default constructor
  front = 0;
  rear = 0;
  capacity = 10; // assume initial queue capacity is 10
  queue = new int[capacity]; // create initial queue array
}

QArray::QArray(int* inputList, int inputSize){
  // parameterised constructor
  front = 0;
  rear = 0;
  capacity = 10; // assume initial queue capacity is 10
  queue = new int[capacity]; // create initial queue array
  for(int i = 0; i < inputSize; i++){
    if(!search(inputList[i])){
      enqueue(inputList[i]);
    }
  }
} 

QArray::~QArray(){
  // destructor
  delete[] queue; // delete the queue array
}

bool QArray::isEmpty(){
  // queue array is empty is front and rear indices are the same
  if(front == rear)
    return true;
  
  return false;
}

bool QArray::isFull(){
  // queue array is full if:
  //  front == (rear + 1) % capacity
  if (front == (rear + 1) % capacity)
    return true;
  
  return false;
}

void QArray::enqueue(const int data){
  // Insert element at the rear end of the queue array
  if(isFull()) { // if queue is full, double queue capacity
    int* newQueue = new int[2 * capacity];
    // copy elements into new array
    for(int i = (front+1) % capacity, j = 0; 
        i != (rear+1)%capacity; 
        i = (i+1) % capacity, j++){
      newQueue[j] = queue[i];
    }
    // Switch to newQueue and set front and rear indices
    // front index is at the end of the array,
    // as front element is at index 0 here
    front = 2 * capacity - 1;
    // queue size is capacity - 1, thus rear element is at index capacity - 2
    rear = capacity - 2;
    capacity = 2 * capacity; // double capacity
    queue = newQueue; // switch to newQueue
    newQueue = nullptr;
  }
  // put the data at the rear end of the queue
  rear = (rear + 1) % capacity;
  queue[rear] = data;
}

int QArray::dequeue(){
  // Delete element from the front end of the queue
  int deletedItem = INT_MIN;
  if(!isEmpty()){
    // get the front element of the queue
    front = (front+1) % capacity;
    deletedItem = queue[front];
    queue[front] = 0; // reset the element at front index
  }
  return deletedItem;
}

bool QArray::search(const int key){
  for(int i = (front+1)%capacity; i != (rear+1)%capacity; i = (i+1)%capacity){
    if(queue[i] == key)
      return true;
  }
  return false;
}

int QArray::getSize(){
  return (rear - front + capacity) % capacity;
}

int QArray::getCapacity(){
  return capacity;
}

int QArray::getFront(){
  // return the element at the front end of the queue
  if(!isEmpty())
    return queue[(front + 1) % capacity];
  // return INT_MIN if queue is empty
  return INT_MIN;
}

int QArray::getRear(){
  // return the element at the rear end of the queue
  if(!isEmpty())
    return queue[rear];
  // return INT_MIN if queue is empty
  return INT_MIN;
}

void QArray::displayQueue(){
  // display circular queue from front to rear
  for(int i = (front+1) % capacity; i != (rear+1)%capacity; i = (i+1) % capacity){
      cout<<queue[i]<<" ";
  }
}