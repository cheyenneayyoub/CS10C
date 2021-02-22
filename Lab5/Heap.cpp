#include "Heap.h"
#include <iostream>

/*Initializes an empty heap.*/
Heap::Heap() {
  numItems = 0;
}

/*Inserts a PrintJob to the heap without
violating max-heap properties.*/
void Heap::enqueue (PrintJob* pj) {
  // 29
  /*

  enqueueHeap(itemType item)
	if heap not full then
		if heap empty then
			arr[numNodes] ← item
			++numNodes
		else 	
			x ← numNodes
			while (x > 0 and arr[(x-1)/2] > item) do
				arr[x] ← arr[(x-1)/2]
				x ← (x-1)/2
			arr[x] ← item
			++numNodes
*/
  if(numItems >= 10)
    return;
  if(numItems == 0) {
    arr[0] = pj;
    ++numItems;
  }
  else {
    int x = numItems;
    while(x > 0 && arr[(x-1)/2]->getPriority() < pj->getPriority()) {
      arr[x] = arr[(x-1)/2];
      x = (x-1)/2;
    }
    arr[x] = pj;
    ++numItems;
  }
}

/*Removes the node with highest priority from the heap. 
Follow the algorithm on priority-queue slides. */
void Heap::dequeue () {
  // slide 46
  if(numItems == 0)
    return;
  if(numItems == 1) {
		  arr[0] = nullptr;
		  numItems = 0;
		  return;
	}
  PrintJob* lastItem = arr[numItems-1];
  arr[0] = lastItem;
  arr[numItems-1] = nullptr;
  numItems--;/*
  if(numItems == 2) { //what would happen if we just took out the if and else? it seemed to work without them yeah
    if(arr[0]->getPriority() >= arr[1]->getPriority())
      return;
  }
  else {
    if(arr[0]->getPriority() >= arr[1]->getPriority() && arr[0]->getPriority() >= arr[2]->getPriority())
      return;
  }
  */
  // if(lastItem->getPriority() >= arr[1]->getPriority() && lastItem->getPriority() >= arr[2]->getPriority()){ //it allows the lastitem to stay at the root if it meets the properties of max heap
  //   return; //this if was the problem 
  // }
  trickleDown(0);
}

  /*Returns the node with highest priority.*/
PrintJob* Heap::highest ( ) {
  if(numItems == 0){
    return 0;
  }
  if(arr[0] == nullptr) {
    if(arr[1] > arr[2])
      return arr[1];
    else
      return arr[2];
  }
  return arr[0];

  /*
  int maxPriority = 0;
  PrintJob* maxPriorityItem = arr[0];
  for(int i = 0 ; i < numItems; i++) {
    if(arr[i]->getPriority() > maxPriority) {
      maxPriority = arr[i]->getPriority();
      maxPriorityItem = arr[i];
    }
  }
  return maxPriorityItem;*/
}

  /*Prints the PrintJob with highest priority in the following format:
  Priority: priority, Job Number: jobNum, Number of Pages: numPages
  (Add a new line at the end.)*/
  void Heap::print ( ) {
    if(numItems == 0) {
      cout << "No items" << endl;
      return;
    }
    cout << "Priority: " << highest()->getPriority() << ", ";
    cout << "Job Number: " << highest()->getJobNumber() << ", ";
    cout << "Number of Pages: " << highest()->getPages() << endl;
  }

  /*This function is called by dequeue function
  to move the new root down the heap to the 
  appropriare location.*/
  void Heap::trickleDown(int n) {
    for(int i = 0; i < numItems; i++) {
		  if(arr[n]->getPriority() < arr[i]->getPriority()) {
          PrintJob* temp = arr[n];
          arr[n] = arr[i];
          arr[i] = temp;
      }
	  }
  }