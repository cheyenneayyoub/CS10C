#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node {
  public:
    Node(string);
    Node* parent;
    Node* left;
    Node* right;
    string data;
    int count;
};

#endif