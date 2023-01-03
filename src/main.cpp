#include <iostream>
#include <ios>
#include <limits>
#include <climits>
#include <string>
#include <sstream>
#include <fstream>
#include "qarray.hpp"
#include "qlist.hpp"
#include "sortedlist.hpp"
#include "bstlist.hpp"
using namespace std; 

enum class errors{
  non_integer_choice,
  file_not_found,
  file_not_supported
};

QList* readFromFiles(){
  // read integers from files into a queue list
  QList* q = new QList(); // empty queue list to store integers from files
  string fileNames, fileName, txtRow, csvRow, num;
  fstream file;
  cout<<"\nNOTE: Duplicate elements will not be inserted!";
  cout<<"\nEnter file names(separated by commas): ";
  cin>>fileNames;
  
  // create a string stream from fileNames
  stringstream fileNamesStream(fileNames);
  
  // parse fileNamesStream to get each file name
  while (fileNamesStream.good()) {
    while(getline(fileNamesStream, fileName, ',')){
      // check type of file
      if(fileName.substr(fileName.find_last_of(".") + 1) == "txt") {
        // for text and tab-separated files
        file.open(fileName, ios::in); // create input file stream to read from file
        // assumes that each row contains a tab-separated list of numbers
        if(file.good()){
          while(file >> txtRow){
            stringstream txtRowStream(txtRow);
            while(getline(txtRowStream, num, '\t')){
              // convert num to int and insert in queue list
              if(num != "")
                q->enqueue(stoi(num));
            }
          }
          file.close();
        }
        else
          throw errors::file_not_found; 
      }
      else if(fileName.substr(fileName.find_last_of(".") + 1) == "csv") {
        // for csv files
        file.open(fileName, ios::in); // create input file stream to read from file
        // assumes that each row contains a comma-separated
        if(file.good()){
          while(file >> csvRow){ 
            stringstream csvRowStream(csvRow);
            while(getline(csvRowStream, num, ',')){
              // convert num to int and insert in queue list
              if(num != "")
                q->enqueue(stoi(num));
            }
          }
          file.close();
        }
        else
          throw errors::file_not_found;
      }
      else
        throw errors::file_not_supported;
    }
  }
  // return pointer to QList object
  return q;
}

void menuQArray(){
  QArray q; // create an empty queue array
  QList* inputList; // list to store file input
  int choice, num;
  do {
    try{
      // display QArray menu
      cout<<"\n\n\t--------Queue Array Menu--------";
      cout<<"\n\t1. Insert from file(s)";
      cout<<"\n\t2. Insert single element";
      cout<<"\n\t3. Remove single element";
      cout<<"\n\t4. Display queue";
      cout<<"\n\t5. Exit and delete queue";
      cout<<"\n\tEnter your choice: ";
      // get user choice
      cin>>choice;

      if(cin.fail()){
        // throw error if non-integer was entered
        cin.clear(); // clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw errors::non_integer_choice;
      }

      switch(choice){
        // perform appropriate action based on choice
        case 1:{
          // read numbers from files and store in queue list
          inputList = readFromFiles();
          // insert elements in inputList into queue
          while(!inputList->isEmpty()){
            num = inputList->dequeue();
            if(!q.search(num)){
              q.enqueue(num); // insert num if it is not in the queue
            }
          }
          cout<<"\nInserted integers from file(s)";
          break;
        }
        case 2:{
          cout<<"\nEnter integer to be inserted: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(!q.search(num)){
            q.enqueue(num); // insert num if it is not in the queue
            cout<<"\nInserted "<<num;
          }
          else 
            cout<<"\n"<<num<<" is already inserted in the queue!";
          break;
        }
        case 3:{
          num = q.dequeue(); // delete front element
          if(num != INT_MIN){
            cout<<"\nDeleted "<<num;
          }
          else
            cout<<"\nQueue is empty, nothing to delete!";
          break;
        case 4:
          if(q.isEmpty())
            cout<<"\nQueue is empty!";
          else{
            cout<<"\nQueue Array: ";
            q.displayQueue();
          }
          break;
        }
        case 5:{
          cout<<"\nQueue will be deleted!";
          break;
        }
        default:{
          cout<<"\nInvalid input! Choice must be between 1 and 5!";
          break;
        }
      }
    } catch(errors err){
      if(err == errors::non_integer_choice) {
        cout<<"\nPlease enter an integer choice/number!\n";
      }
      else if(err == errors::file_not_found) {
        cout<<"\nInput file was not found!\n";
      }
      else if(err == errors::file_not_supported){
        cout<<"\nOnly txt and csv files are supported!\n";
      }
    } 
  }while(choice != 5);
}

void menuQList(){
  QList q; // create an empty queue list
  QList* inputList; // list to store file input
  int choice, num;
  do {
    try{
      // display QList menu
      cout<<"\n\n\t--------Queue List Menu--------";
      cout<<"\n\t1. Insert from file(s)";
      cout<<"\n\t2. Insert single element";
      cout<<"\n\t3. Remove single element";
      cout<<"\n\t4. Display queue";
      cout<<"\n\t5. Exit and delete queue";
      cout<<"\n\tEnter your choice: ";
      // get user choice
      cin>>choice;

      if(cin.fail()){
        // throw error if non-integer was entered
        cin.clear(); // clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw errors::non_integer_choice;
      }

      switch(choice){
        // perform appropriate action based on choice
        case 1:{
          // read numbers from files and store in queue list
          inputList = readFromFiles();
          // insert elements in inputList into queue
          while(!inputList->isEmpty()){
            num = inputList->dequeue();
            if(!q.search(num)){
              q.enqueue(num); // insert num if it is not in the queue
            }
          }
          cout<<"\nInserted integers from file(s)";
          break;
        }
        case 2:{
          cout<<"\nEnter integer to be inserted: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(!q.search(num)){
            q.enqueue(num); // insert num if it is not in the queue
            cout<<"\nInserted "<<num;
          }
          else 
            cout<<"\n"<<num<<" is already inserted in the queue!";
          break;
        }
        case 3:{
          num = q.dequeue(); // delete front element
          if(num != INT_MIN){
            cout<<"\nDeleted "<<num;
          }
          else
            cout<<"\nQueue is empty, nothing to delete!";
          break;
        }
        case 4:{
          if(q.isEmpty())
            cout<<"\nQueue is empty!";
          else{
            cout<<"\nQueue List: ";
            q.displayQueue();
          }
          break;
        }
        case 5:{
          cout<<"\nQueue will be deleted";
          break;
        }
        default:{
          cout<<"\nInvalid input! Choice must be between 1 and 5!";
          break;
        }
      }
    } catch(errors err){
      if(err == errors::non_integer_choice) {
        cout<<"\nPlease enter an integer choice/number!\n";
      }
      else if(err == errors::file_not_found) {
        cout<<"\nInput file was not found!\n";
      }
      else if(err == errors::file_not_supported){
        cout<<"\nOnly txt and csv files are supported!\n";
      }
    } 
  }while(choice != 5);
}

void menuSortedList(){
  SortedList list; // create an empty list
  QList* inputList; // list to store file input
  int choice, num;
  do {
    try{
      // display Sorted List menu
      cout<<"\n\n\t--------Sorted List Menu--------";
      cout<<"\n\t1. Insert from file(s)";
      cout<<"\n\t2. Insert single element";
      cout<<"\n\t3. Remove single element";
      cout<<"\n\t4. Find element";
      cout<<"\n\t5. Display list";
      cout<<"\n\t6. Exit and delete list";
      cout<<"\n\tEnter your choice: ";
      // get user choice
      cin>>choice;

      if(cin.fail()){
        // throw error if non-integer was entered
        cin.clear(); // clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw errors::non_integer_choice;
      }

      switch(choice){
        // perform appropriate action based on choice
        case 1:{
          // read numbers from files and store in queue list
          inputList = readFromFiles();
          // insert elements in inputList into sorted list
          while(!inputList->isEmpty()){
            num = inputList->dequeue();
            list.insert(num);
          }
          cout<<"\nInserted integers from file(s)";
          break;
        }
        case 2:{
          cout<<"\nEnter integer to be inserted: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(!list.search(num)){
            list.insert(num); // insert num if it is not in the list
            cout<<"\nInserted "<<num;
          }
          else 
            cout<<"\n"<<num<<" is already inserted in the list!";
          break;
        }
        case 3:{
          cout<<"\nEnter integer to be deleted: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(list.isEmpty())
            cout<<"\nList is empty, nothing to delete!";
          else if(list.remove(num) != INT_MIN){
            cout<<"\nDeleted "<<num;
          }
          else
            cout<<"\n"<<num<<" is NOT in the list!";
          break;
        }
        case 4:{
          cout<<"\nEnter integer to be searched: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(list.isEmpty())
            cout<<"\nList is empty, nothing to search!";
          else if(list.search(num)){
            cout<<"\n"<<num<<" is present in the list!";
          }
          else
            cout<<"\n"<<num<<" is NOT in the list!";
          break;
        }
        case 5:{
          if(list.isEmpty())
            cout<<"\nList is empty!";
          else{
            cout<<"\nSorted List: ";
            list.displayList();
          }
          break;
        }
        case 6:{
          cout<<"\nList will be deleted";
          break;
        }
        default:{
          cout<<"\nInvalid input! Choice must be between 1 and 5!";
          break;
        }
      }
    } catch(errors err){
      if(err == errors::non_integer_choice) {
        cout<<"\nPlease enter an integer choice/number!\n";
      }
      else if(err == errors::file_not_found) {
        cout<<"\nInput file was not found!\n";
      }
      else if(err == errors::file_not_supported){
        cout<<"\nOnly txt and csv files are supported!\n";
      }
    } 
  }while(choice != 6);
}

void menuBSTList(){
  BSTList tree; // create an empty BST
  QList* inputList; // list to store file input
  int choice, num;
  do {
    try{
      // display BST List menu
      cout<<"\n\n\t--------BST List Menu--------";
      cout<<"\n\t1. Insert from file(s)";
      cout<<"\n\t2. Insert single element";
      cout<<"\n\t3. Remove single element";
      cout<<"\n\t4. Find element";
      cout<<"\n\t5. Display tree in-order";
      cout<<"\n\t6. Exit and delete tree";
      cout<<"\n\tEnter your choice: ";
      // get user choice
      cin>>choice;

      if(cin.fail()){
        // throw error if non-integer was entered
        cin.clear(); // clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw errors::non_integer_choice;
      }

      switch(choice){
        // perform appropriate action based on choice
        case 1:{
          // read numbers from files and store in queue list
          inputList = readFromFiles();
          // insert elements in inputList into sorted list
          while(!inputList->isEmpty()){
            num = inputList->dequeue();
            tree.rootNode = tree.insert(tree.rootNode, num);
          }
          cout<<"\nInserted integers from file(s)";
          break;
        }
        case 2:{
          cout<<"\nEnter integer to be inserted: ";
          cin>>num;
          
          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(!tree.search(tree.rootNode, num)){
            // insert num if it is not in the tree
            tree.rootNode = tree.insert(tree.rootNode, num);
            cout<<"\nInserted "<<num;
          }
          else 
            cout<<"\n"<<num<<" is already inserted in the tree!";
          break;
        }
        case 3:{
          cout<<"\nEnter integer to be deleted: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(tree.isEmpty())
            cout<<"\nTree is empty, nothing to delete!";
          else if(tree.search(tree.rootNode, num)){
            // delete num if it is in the tree
            tree.rootNode = tree.remove(tree.rootNode, num);
            cout<<"\nDeleted "<<num;
          }
          else
            cout<<"\n"<<num<<" is NOT in the tree!";
          break;
        }
        case 4:{
          cout<<"\nEnter integer to be searched: ";
          cin>>num;

          if(cin.fail()){
            // throw error if non-integer was entered
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw errors::non_integer_choice;
          }

          if(tree.isEmpty())
            cout<<"\nTree is empty, nothing to search!";
          else if(tree.search(tree.rootNode, num)){
            cout<<"\n"<<num<<" is present in the tree!";
          }
          else
            cout<<"\n"<<num<<" is NOT in the tree!";
          break;
        }
        case 5:{
          if(tree.isEmpty())
            cout<<"\nTree is empty!";
          else{
            cout<<"\nBST In-order: ";
            tree.displayTreeInOrder(tree.rootNode);
          }
          break;
        }
        case 6:{
          cout<<"\nTree will be deleted";
          break;
        }
        default:{
          cout<<"\nInvalid input! Choice must be between 1 and 5!";
          break;
        }
      }
    } catch(errors err){
      if(err == errors::non_integer_choice) {
        cout<<"\nPlease enter an integer choice/number!\n";
      }
      else if(err == errors::file_not_found) {
        cout<<"\nInput file was not found!\n";
      }
      else if(err == errors::file_not_supported){
        cout<<"\nOnly txt and csv files are supported!\n";
      }
    } 
  }while(choice != 6);
}

void menu(){
  // main menu
  int choice;
  do {
    try{
      // print main menu
      cout<<"\n\n==========MAIN MENU==========";
      cout<<"\nChoose the data structure:";
      cout<<"\n1. Queue Array";
      cout<<"\n2. Queue List";
      cout<<"\n3. Sorted List";
      cout<<"\n4. Binary Search Tree";
      cout<<"\n5. Exit";
      cout<<"\nEnter your choice: ";
      // get user choice
      cin>>choice;

      if(cin.fail()){
        // throw error if non-integer was entered
        cin.clear(); // clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw errors::non_integer_choice;
      }

      switch(choice){
        // display appropriate menu based on choice
        case 1:{
          menuQArray();
          break;
        }
        case 2:{
          menuQList();
          break;
        }
        case 3:{
          menuSortedList();
          break;
        }
        case 4:{
          menuBSTList();
          break;
        }
        case 5:{
          cout<<"\nThank you!\n";
          break;
        }
        default:{
          cout<<"\nInvalid input! Choice must be between 1 and 5!\n";
          break;
        }
      }
    } catch(errors err){
      if(err == errors::non_integer_choice) {
        cout<<"\nPlease enter an integer choice/number!\n";
      }
    }
  }while(choice != 5);
}

int main(){
  // print main menu and get user choice
  try {
     menu();
  } catch(...){
    // catch all block
    cout<<"An Exception has occurred!\n";
  }
  return 0;
}