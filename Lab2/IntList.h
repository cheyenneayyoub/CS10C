/*
Encapsulated (Private) Data Fields

dummyHead: IntNode *
dummyTail: IntNode *

Public Interface (Public Member Functions)

IntList(): Initializes an empty list with dummy head and dummy tail.

~IntList(): Deallocates all remaining dynamically allocated memory (all remaining IntNodes).

void push_front(int value): Inserts a data value (within a new node) at the front end of the list. This must be an O(1) operation.

void pop_front(): Removes the node at the front end of the list (the node after the dummy head). Does nothing if the list is already empty. This must be an O(1) operation.

void push_back(int value): Inserts a data value (within a new node) at the back end of the list. This must be an O(1) operation.

void pop_back(): Removes the node at the back end of the list (the node before the dummy tail). Does nothing if the list is already empty. This must be an O(1) operation.

bool empty() const: Returns true if the list does not store any data values (it only has dummy head and dummy tail), otherwise returns false.

friend ostream & operator<<(ostream &out, const IntList &rhs): A global friend function that outputs to the stream all of the integer values within the list on a single line, each separated by a space. This function does NOT send to the stream a newline or space at the end.

void printReverse() const: prints to a single line all of the int values stored in the list in REVERSE order, each separated by a space. This function does NOT output a newline or space at the end.
*/
#ifndef INTLIST_H
#define INTLIST_H
#include <iostream>

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
  private:
    IntNode* head;
    IntNode* dummyHead;
    IntNode* getTail();
  public:
    IntList();
    ~IntList();
    void push_front(int value);
    void pop_front();
    void push_back(int value);
    void pop_back();
    bool empty() const;
    friend ostream& operator<<(ostream &out, const IntList &rhs);
    void printReverse();
};

#endif