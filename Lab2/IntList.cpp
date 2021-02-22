/*
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
#include <iostream>
#include "IntList.h"

using namespace std;


IntList::IntList() {
  dummyHead = nullptr; // added
  head = dummyHead;
}

IntList::~IntList() {
  while(!empty()){
    pop_front();
  }
}

IntNode* IntList::getTail() { 
  IntNode* temp = head;
  while(temp->next != nullptr) { //going thru the list to find the tail
    temp = temp->next;
  }
  return temp;
}

void IntList::push_front(int value) {
  IntNode* tempA = new IntNode(value);
  if(empty()) {
    head = tempA;
  }
  else {
    IntNode* tempB = head; //make the head the value and push the original head to head->next
    head = tempA;
    head->next = tempB;
    tempB->prev = tempA;
  }
}

void IntList::pop_front() {
  if(empty()) {
    
  }
  else if(head->next == nullptr) { //if there's only 1 item
    // cout << "HEAD->NEXT = NULLPTR" << endl;
    delete head;
    head = dummyHead;
  }
  else { //set a new head to the second item in the list and delete the original head
    // cout << "HEAD->NEXT != NULLPTR" << endl;
    IntNode* temp = head->next;
    delete head;
    head = temp;
    head->prev = nullptr;
    /*
    head = head->next;
    delete temp;
    temp = nullptr;*/
  }
}

void IntList::push_back(int value) {
  IntNode* temp = new IntNode(value);
  if(!empty()){ //temp becomes the new tail
    temp->prev = getTail();
    getTail()->next = temp;
  }
  else{ //if the list is empty
    push_front(value);
  }
}

void IntList::pop_back() {
  if(empty()) {
    //cout << "Empty list." << endl;
  }
  else if(head->next == nullptr) { //if only 1 item
    delete head; head = dummyHead;
  }
  else { //
    IntNode* temp = getTail()->prev; 
    delete getTail();
    temp->next = nullptr;
  }

}

bool IntList::empty() const {
  if(head == dummyHead)
    return true;
  return false;
}

void IntList::printReverse() {
  if(empty()) {
    //cout << "Empty list." << endl;
  }
  else { //looping backwards and printing it
    for(IntNode*temp = getTail(); temp != 0; temp = temp->prev){
      cout << temp->data;
      if(temp->prev != 0){
        cout << " ";
      }
    }
  }
}


ostream& operator<<(ostream &out, const IntList &rhs) {
  out << ""; //
  if(rhs.empty()) {
    //out << "List is empty.";
  }
  else { //looping through and adding a space
    IntNode* temp = rhs.head; 
    while(temp != nullptr){ 
      out << temp->data;
      if(temp->next != nullptr)
        out << " ";
      temp = temp->next;
    }  
  }
  return out;
}

