#ifndef NODE_H 
#define NODE_H 

#include <string>
#include <iostream>

using namespace std;

class Node {
    friend class AVLTree;
       
    public: // was private
      string data; 
      int count;
      Node *parent;
      Node *left;
      Node *right;
      Node(string data);
      int height;
};

#endif