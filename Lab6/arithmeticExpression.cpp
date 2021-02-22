/*
sources:
https://www.geeksforgeeks.org/expression-tree/
https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
*/

#include <iostream>
#include <string>
#include "arithmeticExpression.h"
#include <fstream>
#include <stack>
#include <sstream>

arithmeticExpression::arithmeticExpression(const string &val){
  infixExpression = val;
  root = 0;
}

void arithmeticExpression::buildTree(){
  infixExpression = infix_to_postfix();
  stack<TreeNode*> s;
  TreeNode *t, *t1, *t2;
  char key = 'a';
  for(unsigned i = 0; i < infixExpression.size(); ++i) {
    // If operand, simply push into stack
    if(priority(infixExpression.at(i)) == 0) {
      t = new TreeNode(infixExpression.at(i), i+key);
      s.push(t);
    }
    else { // is operator
      t = new TreeNode(infixExpression.at(i), i+key);
      t1 = s.top(); // store top
      s.pop(); // remove top
      t2 = s.top();
      s.pop();

      // t1 and t2 are now children
      t->right = t1;
      t->left = t2;

      // Add this subexpression to stack
      s.push(t);
      root = t;
    }
  }
  t = s.top();
    s.pop();
}

void arithmeticExpression::infix(){
  infix(root);
}



void arithmeticExpression::prefix(){
  prefix(root);
}



void arithmeticExpression::postfix() {
  postfix(root);
}



void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *ptr){ //needs to be recursive
  if (ptr) {
    outFS << ptr->key << "[ label = " << "\"" << ptr->data << "\"" << " ]" <<endl;
    if (ptr->left) {
        outFS  << ptr->key <<  "->" << ptr->left->key << "[ label = " << "\"" << ptr->left->data << "\"" << " ]" << endl;
        visualizeTree(outFS, ptr->left);
    }
    
    if (ptr->right) {
        outFS  << ptr->key << " -> " << ptr->right->key << "[ label =  " << "\"" << ptr->right->data << "\"" << " ]" << endl;
        visualizeTree(outFS, ptr->right);
    }
    
    outFS << endl;
    }
    
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::infix(TreeNode * node) {
  if (node == nullptr) 
    return;
  
  else if(node->left != nullptr && node->right != nullptr){ 
  cout << "(";
  infix(node->left);
  cout << node->data;
  // char c = node->data;
  // if(!(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')) {
  //   cout << ")";
  // } 
  infix(node->right);
  cout << ")";
  }
  else{
    cout << node->data;
  }
}

void arithmeticExpression::prefix(TreeNode * node) {
  if(node == nullptr){
    return;
  }
  cout << node->data;
  prefix(node->left); 
  prefix(node->right);
  
}

void arithmeticExpression::postfix(TreeNode * node) {
  if (node == nullptr) 
        return;
  postfix(node->left);
  postfix(node->right);
  cout << node->data;
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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

