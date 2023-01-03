// Balanced AVL BST
#include "bstlist.hpp"

BSTList::BSTList(){
  // default constructor
  rootNode = nullptr;
  size = 0;
}

BSTList::BSTList(int* inputList, int inputSize){
  // parameterised constructor
  rootNode = nullptr;
  size = 0;
  // insert elements in tree
  for(int i = 0; i < inputSize; i++)
    rootNode = insert(rootNode, inputList[i]);
}

BSTList::~BSTList(){
  // destructor
  delete rootNode; // will delete the entire tree
}

bool BSTList::isEmpty(){
  // if rootNode is nullptr and size is 0, the tree is empty
  if(this->rootNode == nullptr && this->size == 0)
    return true;
  
  return false;
}

int BSTList::maxHeight(int leftHeight, int rightHeight){
  // return maximum of leftHeight and rightHeight
  return (leftHeight > rightHeight)? leftHeight : rightHeight;
}

int BSTList::getHeight(TNode* node){
  // get height of the sub-tree rooted at node
  if (node == nullptr)
    return 0;
  return node->height;
}

TNode* BSTList::rightRotate(TNode* y){
  // right rotate sub-tree rooted at y
  TNode* x = y->left;
  TNode* T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = 1 + maxHeight(getHeight(y->left), getHeight(y->right));
  x->height = 1 + maxHeight(getHeight(x->left), getHeight(x->right));

  // Return new root
  return x;
}

TNode* BSTList::leftRotate(TNode* y){
  // left rotate sub-tree rooted at y
  TNode* x = y->right;
  TNode* T2 = x->left;

  // Perform rotation
  x->left = y;
  y->right = T2;

  // Update heights
  y->height = 1 + maxHeight(getHeight(y->left), getHeight(y->right));
  x->height = 1 + maxHeight(getHeight(x->left), getHeight(x->right));

  // Return new root
  return x;
}

int BSTList::getBalance(TNode* node){
  // get balance of node
  if (node == nullptr) 
    return 0; 
  return getHeight(node->left) - getHeight(node->right);
}

TNode* BSTList::insert(TNode* root, const int data){
  // insert a node with given data in subtree with given root.
  // It returns root of the modified subtree.

  // 1. Perform the normal BST insertion
  if (root == nullptr){
    // create new TNode and return
    TNode* newNode = new TNode(data);
    this->size++; // increase size of tree
    return newNode;
  }

  if (data < root->key) 
    root->left = insert(root->left, data); 
  else if (data > root->key) 
    root->right = insert(root->right, data); 
  else // Equal keys not allowed 
    return root; 

  // 2. Update height of this ancestor node
  root->height = 1 + maxHeight(getHeight(root->left), getHeight(root->right)); 

  // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
  int balance = getBalance(root); 

  // If this node becomes unbalanced, then there are 4 cases 
  // a. Left Left Case 
  if (balance > 1 && data < root->left->key) 
    return rightRotate(root); 

  // b. Right Right Case 
  if (balance < -1 && data > root->right->key) 
    return leftRotate(root); 

  // c. Left Right Case 
  if (balance > 1 && data > root->left->key) { 
    root->left = leftRotate(root->left); 
    return rightRotate(root); 
  } 

  // d. Right Left Case 
  if (balance < -1 && data < root->right->key) { 
    root->right = rightRotate(root->right); 
    return leftRotate(root); 
  } 

  /* 4. Return the (unchanged) node pointer */
  return root;
}

TNode* BSTList::minValueNode(TNode* root){
  // return the node with minimum value in the tree rooted at root
  TNode* current = root; 
  // loop down to find the leftmost leaf
  while (current->left != nullptr) 
    current = current->left; 

  return current; 
}

TNode* BSTList::remove(TNode* root, const int data){
  // delete a node with given data from subtree with given root. 
  // It returns root of the modified subtree. 

  // Step-1: Perform standard BST delete 
  if (root == nullptr) 
    return root; 

  // If the key to be deleted is smaller than the root's key, then it is in left subtree 
  if (data < root->key) 
    root->left = remove(root->left, data); 

  // If the key to be deleted is greater than the root's key, then it is in right subtree 
  else if(data > root->key) 
    root->right = remove(root->right, data); 

  // If key is same as root's key, then this is the node to be deleted 
  else { 
    // node with only one child or no child 
    if( (root->left == nullptr) || (root->right == nullptr) ) { 
      TNode* temp = root->left ? root->left : root->right; 
      // No child case 
      if (temp == nullptr) { 
        temp = root; 
        root = nullptr; 
      } 
      else // One child case 
        *root = *temp; // Copy the contents of the non-empty child 
      
      this->size--; // decrease size of tree
      free(temp); // delete the node
    } 
    else { 
      // node with two children: Get the inorder successor (smallest in the right subtree) 
      TNode* temp = minValueNode(root->right); 
      // Copy the inorder successor's data to this node 
      root->key = temp->key; 
      // Delete the inorder successor 
      root->right = remove(root->right, temp->key); 
    } 
  } 

  // If the tree had only one node then return 
  if (root == nullptr) 
    return root; 

  // Step-2: Update height of the current node 
  root->height = 1 + maxHeight(getHeight(root->left), getHeight(root->right)); 

  // Step-3: Get the balance of this node
  int balance = getBalance(root); 

  // If this node becomes unbalanced, then there are 4 cases 
  // a. Left Left Case 
  if (balance > 1 && getBalance(root->left) >= 0) 
    return rightRotate(root); 

  // b. Left Right Case 
  if (balance > 1 && getBalance(root->left) < 0) { 
    root->left = leftRotate(root->left); 
    return rightRotate(root); 
  } 

  // c. Right Right Case 
  if (balance < -1 && getBalance(root->right) <= 0) 
    return leftRotate(root); 

  // d. Right Left Case 
  if (balance < -1 && getBalance(root->right) > 0) { 
    root->right = rightRotate(root->right); 
    return leftRotate(root); 
  } 

  return root;
}

bool BSTList::search(TNode* root, const int key){
  // search for key in the sub-tree rooted at root
  if (root == nullptr)
    return false;
  
  if (root->key == key)
    return true;
  
  // Key is greater than root's key
  if (root->key < key)
    return search(root->right, key);

  // Key is smaller than root's key
  return search(root->left, key);
}

int BSTList::getSize(){
  return this->size;
}

TNode* BSTList::getRoot(){
  return this->rootNode;
}

void BSTList::displayTreeInOrder(TNode* root){
  // displays the BST using in-order traversel, which results in a sorted list
  if(root != nullptr) { 
    displayTreeInOrder(root->left); 
    cout << root->key << " ";
    displayTreeInOrder(root->right); 
  }
}
