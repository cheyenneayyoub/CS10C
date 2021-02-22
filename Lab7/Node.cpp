#include "Node.h"


using namespace std;

Node::Node(string data) {
    this->data = data;
    parent = 0;
    left = 0;
    right = 0;
    count = 1;
    height = 0;
}