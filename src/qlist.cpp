// Queue List
#include "qlist.hpp"

QList::QList(){
  // default constructor
  front = nullptr;
  rear = nullptr;
  size = 0;
}

QList::QList(int* inputList, int inputSize){
  // parameterised constructor
  front = nullptr;
  rear = nullptr;
  size = 0;
  // insert elements in queue
  for(int i = 0; i < inputSize; i++){
    if(!search(inputList[i]))
      enqueue(inputList[i]);
  }
}

QList::~QList(){
  // destructor
  delete front; // will delete entire queue
} 

bool QList::isEmpty(){
  // if front and rear are NULL and size is 0, the queue is empty
  if(this->front == nullptr && this->rear == nullptr && this->size == 0)
    return true;
  
  return false;
}

void QList::enqueue(const int data){
  // Insert element at the rear end of the queue list
  // Create a new node
  Node* new_node = new Node(data);

  // If queue is empty, then new node is front and rear both
  if (this->rear == nullptr) {
    this->front = new_node;
    this->rear = new_node;
  }
  // Add the new node at the end of queue and change rear
  else{
    this->rear->next = new_node;
    this->rear = new_node;
  }
  this->size++; // increment size of queue
}

int QList::dequeue(){
  // Delete element from the front end of the queue list
  int deletedItem = INT_MIN;

  if (this->front != nullptr){
    // Store previous front and move front one node ahead
    Node* temp = this->front;
    this->front = this->front->next;

    // If front becomes NULL, then  change rear also as NULL
    if (this->front == nullptr)
      this->rear = nullptr;

    deletedItem = temp->data;
    free(temp); // delete node
    this->size--; // decrease size of the queue
  }
  // if queue is empty, INT_MIN is returned,
  // else element at the front of the queue is returned
  return deletedItem;
}

bool QList::search(const int key){
  // check if key is present in the queue
  Node* current = this->front;
  while (current != nullptr) {
    if (current->data == key)
      return true;
    current = current->next;
  }
  // false is returned when key is not in the queue
  return false;
}

int QList::getSize(){
  return this->size;
}

Node* QList::getFront(){
  return this->front;
}

Node* QList::getRear(){
  return this->rear;
}

void QList::displayQueue(){
  // print the queue from front to rear
  Node* temp = this->front;
  while (temp != nullptr) {
    cout << temp->data << " ";
    temp = temp->next;
  }
}