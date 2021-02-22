#include "Node.h"
#include <string>

using namespace std;

Node::Node(string data) {
	this->data = data;
	left = 0;
	right = 0;
	parent = 0;
	count = 1;
}