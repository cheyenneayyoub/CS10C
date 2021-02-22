#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <stdexcept>

#define MAX_SIZE 20

using namespace std;

template <typename T>
class stack {
  private:
  T data[MAX_SIZE];
  int size;
  public:
  stack();
  void push(T);
  void pop();
  T top();
  bool empty();
};


template <typename T>
stack<T>::stack(){ //constructs an empty stack
  size = 0;
}

template <typename T>
void stack<T>::push(T val){ //inserts a new element (val) of type T (T could be integer or string) into the data. If the data array is full, this function should throw an overflow_error exception with error message "Called push on full stack.".
  if (size != MAX_SIZE){
    data[size] = val;
    size++;
  }
  else{
    throw overflow_error("Called push on full stack.");
  }

}

template <typename T>
void stack<T>::pop(){ //removes the last element from data. If the data array is empty, this function should throw an outofrange exception with error message "Called pop on empty stack.".
  if (size == 0){
    throw out_of_range("Called pop on empty stack.");
  }
  else{
    size--;
  }
}

template <typename T>
T stack<T>::top(){ //returns the top element of stack (last inserted element). If stack is empty, this function should throw an underflow_error exception with error message "Called top on empty stack.".
  if (size == 0){
    throw underflow_error("Called top on empty stack.");
  }
  else{
    return data[size-1];
  }
}

template <typename T>
bool stack<T>::empty(){ //returns true if the stack is empty otherwise it returns false.
  if (size == 0){
    return true;
  }
  else{
    return false;
  }
}

#endif