/*
Sources:
Zybooks, GeeksForGeeks, Paul Programming
*/

#include <iostream>
#include <string>
#include "BSTree.h"
#include "Node.h"

using namespace std;

        /* Constructors */
        /* Default constructor */
BSTree::BSTree() {
  root = nullptr;
}
BSTree::~BSTree() {
  // ref https://www.youtube.com/watch?v=ozBhVQNSJ9E
  RemoveSubtree(root);
}

Node* BSTree::getRoot() {
  return root;
}

void BSTree::RemoveSubtree(Node* cur) {
    if(cur != nullptr) { 
      if(cur->left != nullptr) {
        RemoveSubtree(cur->left);
      }
      if(cur->right != nullptr) {
        RemoveSubtree(cur->right);
      }
      delete cur;
    }
  }
        /* Mutators */
        /* Insert an item into the binary search tree. 
           Be sure to keep BST properties. 
           When an item is first inserted into the tree the count should be set to 1. 
           When adding a duplicate string (case sensitive), rather than adding another node, 
           the count variable should be incremented 
         */
void BSTree::insert(const string &newString) {
  // ref Zybooks
  if(find(newString)) { //to increment count
    find(newString)->count++;
    return;
  }
    Node* node = new Node(newString);
    if(root == nullptr) { //if theres nothing in the tree
      root = node;
    }
    else {
      Node* cur = root;
      while(cur != nullptr) {
          if(node->data < cur->data) { //left subtree
            if(cur->left == nullptr) { //if it's a leaf
              cur->left = node;
              cur = nullptr;
            }
            else { //if not a leaf then iterate thru
              cur = cur->left;
            }
          }
          else if(node->data == cur->data){
            cur->count = cur->count+1;
          }
          else { //right subtree
            if(cur->right == nullptr) { //if it's a leaf
              cur->right = node;
              cur = nullptr;
            }
            else {
              cur = cur->right;
            }
          }
      }
    }
}
        /* Remove a specified string from the tree. 
           Be sure to maintain all bianry search tree properties. 
           If removing a node with a count greater than 1, just decrement the count, otherwise, 
           if the count is simply 1, remove the node. 
            You MUST follow the remove algorithm shown in the slides and discussed in class or else 
            your program will not pass the test functions. 
            When removing, 
                if removing a leaf node, simply remove the leaf. Otherwise, 
                if the node to remove has a left child, replace the node to remove with the largest 
                string value that is smaller than the current string to remove 
                (i.e. find the largest value in the left subtree of the node to remove). 
                If the node has no left child, replace the node to remove with the smallest value 
                larger than the current string to remove 
                (i.e. find the smallest value in the right subtree of the node to remove. 
         */
void BSTree::remove(const string &key) { //algorithm from zybooks
  if(find(key)) { //to iterate count
    if(find(key)->count > 1) {
      find(key)->count--;
      return;
    }
  }
  Node* par = nullptr;
  Node* cur = root;
  while (cur != nullptr) { // Search for node
    if (cur->data == key) { // Node found 
      if (cur->left == nullptr && cur->right == nullptr) { // Remove leaf
        if (par == nullptr) { // Node is root
          delete root;
          root = nullptr;
        }
        else if (par->left == cur) { //left leaf
          delete cur;
          par->left = nullptr;
        }
        else { //right leaf
          delete cur;
          par->right = nullptr;
        }
      }
      else if (cur->right == nullptr) { // Remove node with only left child
        if (par == nullptr) { // Node is root
          root = cur->left;
          delete cur;
        }
        else if (par->left == cur) { 
          par->left = cur->left;
          delete cur;
        }
        else {
          par->right = cur->left;
          delete cur;
        }
      }
      else if (cur->left == nullptr) { // Remove node with only right child
        if (par == nullptr) { // Node is root
          root = cur->right;
          delete cur;
        }
        else if (par->left == cur) {
          par->left = cur->right;
          delete cur;
        }
        else {
          par->right = cur->right;
          delete cur;
        }
      }
      else { // Remove node with two children
            // Find successor (leftmost child of right subtree)
        Node* suc = cur->right;
        while (suc->left != nullptr){ //going to leftmost node in right subtree
          suc = suc->left;
        }
        string successorData = suc->data; //Create copy of suc's data
        int sucCount = suc->count;
        for(int i = 0; i < sucCount; i++) {
          remove(suc->data);
        }     // Remove successor
        // Assign cur's data with successorData
        cur->data = successorData;
        cur->count = sucCount;
      }
         return; // Node found and removed
    }
    else if (cur->data < key) { // Search right
      par = cur;
      cur = cur->right;
    }
    else {                     // Search left
      par = cur;
      cur = cur->left;
    }
   }
   return; // Node not found
}


        /* Accessors */
        /* Search for a string in the binary search tree. 
           It should return true if the string is in the tree, and false otherwise. 
         */
bool BSTree::search(const string &key) const {
  Node* cur = root;
  while (cur != nullptr){
    if(cur->data == key){
      cout << key << " Was found" << endl;
      return true;
    }
    if (cur->data < key) {
			cur = cur->right;
		}
		else {
			cur = cur->left;
		}
  }
  cout << key << " Was not found" << endl;
  return false;
}

/*

cur = tree⇢root
   while (cur is not null) {
      if (key == cur⇢key) {
         return cur // Found
      }
      else if (key < cur⇢key) {
         cur = cur⇢left
      }
      else {
         cur = cur⇢right
      }
   }
   return null // Not found

   */

   Node* BSTree::find(string data) const {
     Node* cur = root;
     while(cur != nullptr) {
       if(data == cur->data) {
         return cur;
       }
       else if(data < cur->data) {
         cur = cur->left;
       }
       else {
         cur = cur->right;
       }
     }
     return nullptr;
}

string BSTree::largest() const {
  string largest = "";
  if (root != nullptr){
    Node* cur = root;
    while (cur->right != nullptr){ //going to the rightmost node bc it'll be the biggest
      cur = cur->right;
    }
    largest = cur->data;
  }
  return largest;
}
        /* Find and return the smallest value in the tree. Return an emtpy string if the tree is empty */
string BSTree::smallest() const {
  string smallest = "";
  if (root != nullptr){ //goes to leftmost node
    Node* cur = root;
    while (cur->left != nullptr){
      cur = cur->left;
    }
    smallest = cur->data;
  }
  return smallest;
}
        /* Compute and return the height of a particular string in the tree. 
           The height of a leaf node is 0 (count the number of edges on the longest path). 
           Return -1 if the string does not exist. 
         */

int BSTree::getHeight(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    else if (node->left == nullptr && node->right == nullptr) {
      return 0;
    }
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    
    if (leftHeight > rightHeight) {
      return leftHeight + 1;
    }
    else {
      return rightHeight + 1;
    }
    
    return 0;
}        

int BSTree::height(const string& str) const {
  // ref https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
  // Node* node = nullptr;
  // node->data = str;

  // if(node == nullptr){
  //   return -1;
  // }
  // int lDepth = height(node->left->data);
  // int rDepth = height(node->right->data);
  // if(lDepth > rDepth)
  //   return (lDepth + 1);
  // else
  //   return (rDepth + 1);
  
  Node* rootNode = find(str);
	
	if (rootNode == nullptr) {
		return -1;
	}
	
	if (rootNode->left == nullptr && rootNode->right == nullptr) {
		return 0;
	}
	
	return getHeight(rootNode);
}

        /* Printing */
        /* For all printing orders, each node should be displayed as follows:
           <string> (<count>)
           e.g. goodbye(1), Hello World(3)
           */
void BSTree::preOrder() const {
  preOrder(root);
}

void BSTree::postOrder() const {
  postOrder(root);
}

void BSTree::inOrder() const {
  inOrder(root);
}

void BSTree::preOrder(Node* cur) const{
  if (cur != nullptr){
    cout << cur->data << "(" << cur->count << "), ";
    preOrder(cur->left);
    preOrder(cur->right);
  }
  else{
    return;
  }
}

void BSTree::inOrder(Node* cur) const {
  if (cur != nullptr){
    inOrder(cur->left);
    cout << cur->data << "(" << cur->count << "), ";
    inOrder(cur->right);
  }
  else{
    return;
  }
}

void BSTree::postOrder(Node* cur) const{
  if(cur != nullptr){
    postOrder(cur->left);
    postOrder(cur->right);
    cout << cur->data << "(" << cur->count << "), ";
  }
  else{
    return;
  }
}