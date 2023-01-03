/*
  This program runs the insert, delete and search functions
  for QArray, QList, SortedList, BSTList for various input
  sizes and records the execution time in a CSV file.
*/ 

#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include "src/qarray.hpp"
#include "src/qlist.hpp"
#include "src/sortedlist.hpp"
#include "src/bstlist.hpp"
using namespace std;

class CSVRow {
  public:
    string dataStructure;
    string operation;
    int inputSize;
    int dataSize;
    int execTime; // in nanoseconds

    CSVRow(){
      this->dataStructure = ""; 
      this->operation = "";
      this->inputSize = 0;
      this->dataSize = 0;
      this->execTime = 0;
    }

    CSVRow(
      string dataStructure, 
      string operation,
      int inputSize,
      int dataSize,
      int execTime){
      this->dataStructure = dataStructure; 
      this->operation = operation;
      this->inputSize = inputSize;
      this->dataSize = dataSize;
      this->execTime = execTime;
    }
}; 

QList* readFromTxtFile(string fileName){
  // read integers from txt files into a queue list
  QList* q = new QList(); // empty queue list to store integers from files
  fstream file(fileName, ios::in);
  int num;
  // assumes that each row contains a tab-separated list of numbers
  if(file.good()){
    while(file >> num)
      q->enqueue(num);
    file.close();
  }
  else
    throw -1;
  // return pointer to QList object
  return q;
}

void writeToCsv(vector<CSVRow> rows){
  fstream csvFileIn("graph/function_time_data.csv", ios::in);
  fstream csvFileOut("graph/function_time_data.csv", ios::out | ios::app);
  // write column headers if file is empty
  if(csvFileIn.peek() == std::ifstream::traits_type::eof()){
    // file is empty
    csvFileOut << "data_structure,"
          << "operation,"
          << "input_size,"
          << "data_size,"
          << "time_nano\n";
  }
  // write data to file
  for(auto &row: rows){ // create reference, does not create a copy
    csvFileOut << row.dataStructure << "," 
            << row.operation << ","
            << row.inputSize << ","
            << row.dataSize << ","
            << row.execTime << "\n";            
  }
  csvFileIn.close();
  csvFileOut.close();
}

int main(){
  int testInputSizes[] = {10,20,40,80,160,320,640,1280,2560,5120,10240};
  int inputSizesLen = 11;
  int numTest = 1, testInput = 10001, num = 0;
  QList* inputList; // to store number read from file
  string inputFile;
  vector<CSVRow> rows; // vector to store data
  std::chrono::high_resolution_clock::time_point startTime, endTime;
  std::chrono::duration<int, std::nano> span;

  for(int i = 0; i < inputSizesLen; i++){
    QArray qarr; // empty queue array
    QList qlist; // empty queue list
    SortedList list; // empty list
    BSTList tree; // empty tree


    inputFile = "test/txt/rev-sorted-{}-input.txt";
    inputFile.replace(inputFile.find('{'),2,to_string(testInputSizes[i]));
    inputList = readFromTxtFile(inputFile);
    // insert elements from file first
    for(int j = 0; j < testInputSizes[i] - 1; j++){
      num = inputList->dequeue();
      // insert num in qarr, qlist, sorted list and tree
      if(!qarr.search(num)){
        qarr.enqueue(num);
      }
      if(!qlist.search(num)){
        qlist.enqueue(num);
      }
      list.insert(num);
      tree.rootNode = tree.insert(tree.rootNode, num);
    }

    // perform insert, search, delete for 'testInput' 'numTest' times
    for(int j = 0; j < numTest; j++){
       /* 
        for queue array:
        1. worst case input(enqueue): no. of elements = queue capacity - 1
        2. worst case input(search): key is not in the queue or at the end
      */
      // qarray insert
      startTime = std::chrono::high_resolution_clock::now();

      qarr.enqueue(testInput+j);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("q_array", "insert", testInputSizes[i], qarr.getSize(), span.count()));
      
      // qarray search
      startTime = std::chrono::high_resolution_clock::now();

      qarr.search(testInput+j);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("q_array", "search", testInputSizes[i], qarr.getSize(), span.count()));
      
      // qarray delete
      startTime = std::chrono::high_resolution_clock::now();

      qarr.dequeue();

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("q_array", "delete", testInputSizes[i], qarr.getSize(), span.count()));



      /* 
        for queue list:
        1. worst case input(search): key is not in the queue or at the end
      */
      // qlist insert
      startTime = std::chrono::high_resolution_clock::now();

      qlist.enqueue(testInput+j);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("q_list", "insert", testInputSizes[i], qlist.getSize(), span.count()));
      
      // qlist search
      startTime = std::chrono::high_resolution_clock::now();

      qlist.search(testInput+j);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("q_list", "search", testInputSizes[i], qlist.getSize(), span.count()));
      
      // qlist delete
      startTime = std::chrono::high_resolution_clock::now();

      qlist.dequeue();

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("q_list", "delete", testInputSizes[i], qlist.getSize(), span.count()));

      /* 
        for sorted list:
        1. worst-case input(insert): reverse sorted list
        2. worst case input(search): key is not in the list or at the end
      */
      // sorted list insert
      startTime = std::chrono::high_resolution_clock::now();

      list.insert(testInput);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("sorted_list", "insert", testInputSizes[i], list.getSize(), span.count()));
      
      // sorted list search
      startTime = std::chrono::high_resolution_clock::now();

      list.search(testInput);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("sorted_list", "search", testInputSizes[i], list.getSize(), span.count()));
      
      // sorted list delete
      startTime = std::chrono::high_resolution_clock::now();

      list.remove(testInput);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("sorted_list", "delete", testInputSizes[i], list.getSize(), span.count()));

      /* 
        for BST:
        1. worst case input(insert): sorted or reverse sorted list (most rotations during insert)
        2. worst case input(search): key is not in the tree or at the end
      */
      // bst insert
      startTime = std::chrono::high_resolution_clock::now();

      tree.rootNode = tree.insert(tree.rootNode, testInput);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("binary_search_tree", "insert", testInputSizes[i], tree.getSize(), span.count()));
      
      // bst search
      startTime = std::chrono::high_resolution_clock::now();

      tree.search(tree.rootNode, testInput);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("binary_search_tree", "search", testInputSizes[i], tree.getSize(), span.count()));
      
      // sorted list delete
      startTime = std::chrono::high_resolution_clock::now();

      tree.rootNode = tree.remove(tree.rootNode, testInput);

      endTime = std::chrono::high_resolution_clock::now();
      span = endTime - startTime;
      rows.push_back(CSVRow("binary_search_tree", "delete", testInputSizes[i], tree.getSize(), span.count()));
    }
  }
  // write data into csv file
  writeToCsv(rows);
  return 0;
}

/**
  Command to build the file:
  1. Go to source-code directory
  2. Run: g++ get_function_times.cpp src/qarray.cpp src/qlist.cpp src/sortedlist.cpp src/bstlist.cpp src/node.cpp src/tnode.cpp -std=c++11 -o output/get_function_time -I $(pwd) 
  
  Command to run the executable:
  1. Go to source-code directory
  2. mkdir -p output
  2. Run: ./output/get_function_time
*/