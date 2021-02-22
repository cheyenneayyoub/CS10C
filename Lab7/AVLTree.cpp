#include "AVLTree.h"

AVLTree::AVLTree() : root(0){}

void AVLTree::insert(const string &str){ //Insert an item to the binary search tree and perform rotation if necessary.
//algorithm from zybooks
   Node* curr = root;
    while (curr){ //loop thru to find where to insert it
        if (curr->data > str){ //if root > str
            curr = curr->left;
        }
        else if (curr->data < str){ //if root < str
            curr = curr->right;
        }
        else{
            return;
        }
    }

    Node* node = new Node(str);
    if (!root){ //create new node and set root equal to the node and node's parent to null
        root = node;
        node->parent = nullptr;
        return;
    }

    Node* cur = root;
    while (cur){
        if (node->data < cur->data){ // if node's data < root's data
            if (!cur->left){ 
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }
            else{
                cur = cur->left;
            }
        }
        else{ //if node's data > root's data then go right
            if (!cur->right){
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }
            else{
                cur = cur->right;
            }
        }
    }

    node = node->parent;

    while (node){
        AVLTreeRebalance(node);
        node = node->parent;
    }

}

int AVLTree::balanceFactor(Node* node){ //Return the balance factor of a given node.
  int ht = 0;
  if(node == nullptr){
    return 0;
  }
  else{
    ht = height(node->left) - height(node->right);
  }
  return ht;
}

void AVLTree::printBalanceFactors(){ //Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.

  printBalanceFactors(root);
  cout << endl;
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    // string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    // string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    // system(command.c_str());
}

Node* AVLTree::findUnbalancedNode(Node * node){ //Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
  if (node == 0) {
    return 0;
  }
   
  int bFactor = balanceFactor(node);
  if (bFactor == -2 || bFactor == 2) {
    return node;
  }
  else {
    return findUnbalancedNode(node->parent);
  }
}


void AVLTree::AVLTreeRebalance(Node* node) {
  //cout << "rebalance" << endl;
   height(node);        
   if (balanceFactor(node) == -2) {
      if (balanceFactor(node->right) == 1) {
         // Double rotation case.
         rotateRight(node->right);
      }
      rotateLeft(node);
   }
   else if (balanceFactor(node) == 2) {
      if (balanceFactor(node->left) == -1) {
         // Double rotation case.
         rotateLeft(node->left);
      }
      rotateRight(node);
   }     
}

void AVLTree::rotate(Node* node){ //Implement four possible imbalance cases and update the parent of the given node.
  updateHeight(node);      
  if (getBalance(node) == -2) {
    if (getBalance(node->right) == 1) {
      // Double rotation case.
      rotateRight(node->right);
    }
    rotateLeft(node);
  }
  else if (getBalance(node) == 2) {
    if (getBalance(node->left) == -1) {
      // Double rotation case.
      rotateLeft(node->left);
    }
    rotateRight(node); // was return rotateRight(node)
  }        
  // return node;
}

void AVLTree::rotateLeft(Node* node){ //Rotate the subtree to left at the given node and returns the new subroot.
  Node* rightLeftChild = node->right->left;
  if (node->parent != nullptr){
    replaceChild(node->parent, node, node->right);
  }
  else { // node is root
    root = node->right;
    root->parent = nullptr;
  }
  setChild(node->right, "left", node);
  setChild(node, "right", rightLeftChild);
}

/*
Zybooks
AVLTreeRotateRight(tree, node) {
   leftRightChild = node->left->right
   if (node->parent != null)
      AVLTreeReplaceChild(node->parent, node, node->left)
   else { // node is root
      tree->root = node->left
      tree->root->parent = null
   }
   AVLTreeSetChild(node->left, "right", node)
   AVLTreeSetChild(node, "left", leftRightChild)
}
*/
void AVLTree::rotateRight(Node* node){ //Rotate the subtree to right at the given node and returns the new subroot.
  Node* leftRightChild = node->left->right;
  if (node->parent != nullptr){
    replaceChild(node->parent, node, node->left);
  }
  else { // node is root
    root = node->left;
    root->parent = nullptr;
  }
  setChild(node->left, "right", node);
  setChild(node, "left", leftRightChild);
}// ->

void AVLTree::printBalanceFactors(Node *node){
  if(node){
    printBalanceFactors(node->left);
    cout << node->data << "(" << balanceFactor(node) << "), ";
    printBalanceFactors(node->right);
  }
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}

int AVLTree::height(Node* node){ //used from BST 
  if (node == nullptr) {
      return -1;
    }
  else if (node->left == nullptr && node->right == nullptr) {
    return 0;
  }
    
  int leftHeight = height(node->left);
  int rightHeight = height(node->right);
    
  if (leftHeight > rightHeight) {
    return leftHeight + 1;
  }
  else {
    return rightHeight + 1;
  }
    
  return 0;
}

/*
AVLTreeUpdateHeight(node) {
   leftHeight = -1
   if (node->left != null)
      leftHeight = node->left->height
   rightHeight = -1
   if (node->right != null)
      rightHeight = node->right->height
   node->height = max(leftHeight, rightHeight) + 1
}
*/
void AVLTree::updateHeight(Node* node) {
  int leftHeight = -1;
  if (node->left != nullptr){
    leftHeight = node->left->height;
  }
  int rightHeight = -1;
  if (node->right != nullptr){
    rightHeight = node->right->height;
  }
  node->height = max(leftHeight, rightHeight) + 1;
}

/*
AVLTreeSetChild(parent, whichChild, child) {
   if (whichChild != "left" && whichChild != "right")
      return false

   if (whichChild == "left")
      parent->left = child
   else
      parent->right = child
   if (child != null)
      child->parent = parent

   AVLTreeUpdateHeight(parent)
   return true
}
*/
bool AVLTree::setChild(Node* parent, string whichChild, Node* child) {
  if (whichChild != "left" && whichChild != "right")
      return false;

  if (whichChild == "left")
    parent->left = child;
  else
    parent->right = child;
  if (child != nullptr)
      child->parent = parent;

   updateHeight(parent);
   return true;
}

/*
AVLTreeReplaceChild(parent, currentChild, newChild) {
   if (parent->left == currentChild)
      return AVLTreeSetChild(parent, "left", newChild)
   else if (parent->right == currentChild)
      return AVLTreeSetChild(parent, "right", newChild)
   return false
}
*/
bool AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild) {
  if (parent->left == currentChild){
    return setChild(parent, "left", newChild);
  }
  else if (parent->right == currentChild){
    return setChild(parent, "right", newChild);
  }
  return false;
}

/*
AVLTreeGetBalance(node) {
   leftHeight = -1
   if (node->left != null)
      leftHeight = node->left->height
   rightHeight = -1
   if (node->right != null)
      rightHeight = node->right->height
   return leftHeight - rightHeight
}
*/
int AVLTree::getBalance(Node* node) {
  int leftHeight = -1;
  if (node->left != nullptr)
    leftHeight = node->left->height;
  int rightHeight = -1;
  if (node->right != nullptr)
    rightHeight = node->right->height;
  return leftHeight - rightHeight;
}