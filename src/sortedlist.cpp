// Sorted List
#include "sortedlist.hpp"

SortedList::SortedList(){
  // default constructor
  head = nullptr;
  size = 0;
}

SortedList::SortedList(int* inputList, int inputSize){
  // parameterised constructor
  head = nullptr;
  size = 0;
  // insert elements in list
  for(int i = 0; i < inputSize; i++)
    insert(inputList[i]);
}

SortedList::~SortedList(){
  // destructor
  delete head; // will delete the entire list
}

bool SortedList::isEmpty(){
  // if head is nullptr and size is 0, the list is empty
  if(this->head == nullptr && this->size == 0)
    return true;
  
  return false;
}

void SortedList::insert(const int data){
  // insert a new node with data in the sorted list
  // Special case for the head end
  if (this->head == nullptr || this->head->data > data){
    Node* new_node = new Node(data);
    new_node->next = this->head;
    this->head = new_node;
    this->size++; // increase the size of list
  }
  else if (this->head->data != data) { // duplicate data is not inserted
    // Locate the node before the point of insertion
    Node* current = this->head;
    while (current->next != nullptr && current->next->data < data)
      current = current->next;
    // Check if data is not a duplicate entry
    if(current->next == nullptr || current->next->data != data){
      Node* new_node = new Node(data);
      new_node->next = current->next;
      current->next = new_node;
      this->size++; // increase the size of list
    }
  }
}

int SortedList::remove(const int data){
  // delete data from the sorted list
  Node* temp = this->head; // Store head node
  Node* prev = nullptr;
  int deletedItem = INT_MIN;
    
  // If head node itself holds the key to be deleted
  if (temp != nullptr && temp->data == data){
    this->head = temp->next; // Changed head
    deletedItem = temp->data;
    free(temp); // free old head
    this->size--; // decrease size
  }
  // Else Search for the key to be deleted
  else{
    while (temp != nullptr && temp->data != data){
      prev = temp;
      temp = temp->next;
    }
    // If key is present in sorted list
    if (temp != nullptr){
      // Unlink the node from linked list
      prev->next = temp->next;
      deletedItem = temp->data;
      free(temp); // Free memory
      this->size--; // decrease size
    }
  }
  // INT_MIN is returned if the item was not present in the list, 
  // else the item which was deleted is returned
  return deletedItem;
}

bool SortedList::search(const int key){
  // check if key is present in the list
  Node* current = this->head;
  while (current != nullptr) {
    if (current->data == key)
      return true;
    current = current->next;
  }
  // false is returned when key is not in the list
  return false;
}

int SortedList::getSize(){
  return this->size;
}

Node* SortedList::getHead(){
  return this->head;
}

void SortedList::displayList(){
  // print the list from the head to the end
  Node* temp = this->head;
  while (temp != nullptr) {
    cout << temp->data << " ";
    temp = temp->next;
  }
}