// Balanced AVL BST
#include "tnode.hpp"

class BSTList {
  public:
    // data members
    TNode* rootNode; // root node reference
    int size; // size of tree

    // operations
    BSTList(); // default constructor
    BSTList(int* inputList, int inputSize); // constructor
    ~BSTList(); // destructor
    bool isEmpty();
    int maxHeight(int leftHeight, int rightHeight);
    int getHeight(TNode* node);
    TNode* rightRotate(TNode* node);
    TNode* leftRotate(TNode* node);
    int getBalance(TNode* node);
    TNode* insert(TNode* root, const int data);
    TNode* remove(TNode* root, const int data);
    TNode* minValueNode(TNode* root);
    bool search(TNode* root, const int key);
    int getSize();
    TNode* getRoot();
    void displayTreeInOrder(TNode* root);
};