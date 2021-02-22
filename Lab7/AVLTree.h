/*
findUnbalancedNode: Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
rotate: Implement four possible imbalance cases and update the parent of the given node.
rotateLeft: Rotate the subtree to left at the given node and returns the new subroot.
rotateRight: Rotate the subtree to right at the given node and returns the new subroot.
void printBalanceFactors(Node *)
void visualizeTree(ofstream &, Node *)
*/

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include "Node.h"
#include <fstream>
#include <string>

using namespace std;
class AVLTree{
  public:
    AVLTree();
    void insert(const string &);
    int balanceFactor(Node*);
    void printBalanceFactors();
    void visualizeTree(const string &);
  private:
    Node* findUnbalancedNode(Node*);
    void rotate(Node* );
    void rotateLeft(Node* );
    void rotateRight(Node* );
    void printBalanceFactors(Node *);
    void visualizeTree(ofstream &, Node *);
    Node* root;
    int height(Node*);
    void AVLTreeRebalance(Node* );
    void updateHeight(Node* );
    bool setChild(Node* , string , Node* );
    bool replaceChild(Node* , Node* , Node* );
    int getBalance(Node* );
    
};

#endif