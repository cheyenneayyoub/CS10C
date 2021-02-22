#include "WordLadder.h"
#include <fstream>
#include <sstream>
#include <iostream>

WordLadder::WordLadder(const string & file){
  ifstream inFS;
  inFS.open(file);
  if (!inFS.is_open()){
    cout << "Error: could not open file." << endl;
    return;
  }
  string word = "";
  while(!inFS.eof()){ 
    inFS >> word;
    if(word.size() > 5 || word.size() < 5){
      cout << "Word needs to have 5 letters" << endl;
      return;
    }
    dict.push_back(word);
  }
  inFS.close();
  return; 
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile){
  ofstream outFS;
  outFS.open(outputFile);
  if(!outFS.is_open()){ 
    cout << "Error: could not open file." << endl;
    return;
  }
  
  //need to check the start & end word exists
  list<string>::iterator iter;
  int count = 0;
  int count_1 = 0;

  for (iter = dict.begin(); iter != dict.end(); iter++) {
      if (start == *iter) {
        count++;
      }
      if(end == *iter){
        count_1++;
      }
  }
  //if the word doesn't exist
  if(count == 0){
    cout << "Could not find first word entered." << endl;
    return;
  }
  else if(count_1 == 0){
    cout << "Could not find last word entered." << endl;
    return;
  }
  else if(count_1 == 0 && count == 0){
    cout << "Could not find both words entered." << endl;
    return;
  }

  if(start == end){
    outFS << start << endl;
    outFS.close();
    return;
  }
  // else{ //actual word ladder part
    queue<stack<string>> queueStack;
    stack<string> temp; 
    stack<string> newStack;
    // string topWord;
    
  //   temp.push(start); //stack with first word in the ladder
  //   queueStack.push(temp); //putting the stack into the front of the queue
  //   while(!queueStack.empty()){
      
  //     newStack = queueStack.front(); //need first word of first stack
      
  //     topWord = newStack.top();
  //     for(iter = dict.begin(); iter != dict.end();){ //go thru dict
  //         unsigned count_2 = 0;
  //         string curr = *iter;
           
  //         for(unsigned i = 0; i < topWord.size(); i++){
  //           if(topWord.at(i) != curr.at(i)){
  //             count_2++;
  //           }
  //         }
  //         if (count_2 <= 1){ //only one letter off
  //           stack<string> copyStack = newStack;
  //           copyStack.push(*iter);
  //           if(*iter == end){ 
  //             list<string> finalList;
  //             while(!copyStack.empty()){
  //               finalList.push_front(copyStack.top());
  //               copyStack.pop();
  //             }
  //             for(iter = finalList.begin(); iter != finalList.end(); iter++){
  //               outFS << *iter << " ";
  //             }
  //             outFS << endl;
  //             outFS.close();
  //             return;
  //           }
  //           else{ //enqueue the stack and remove word from dict
  //             queueStack.push(copyStack);
  //             iter = dict.erase(iter);

  //           }
  //         }
  //         else{
  //           iter++;
  //         }

  //     }
  //   }
  //   queueStack.pop();
  //   if(queueStack.empty()){
  //     outFS << "No Word Ladder Found." << endl;
  //   }
  // // }

  // outFS.close();
  // return;


  string topWord;
  temp.push(start);
  queueStack.push(temp);
  //not empty
  while (!queueStack.empty()) {
    newStack  = queueStack.front();
    topWord = newStack.top();
    //iterate from beginning to end of the dictionary
    for (iter = dict.begin(); iter != dict.end();) {
      unsigned counter = 0;
      string curr = *iter;
      for (unsigned j = 0; j < topWord.size(); ++j ) {
          if (topWord.at(j) != curr.at(j)) {
            counter++;
          }
      }
      if (counter <= 1) {
        //push the strings onto stack
        stack<string> copyStack = newStack;
        copyStack.push(*iter);
        if (*iter == end) {
          list<string> finalList;
          //transfer the the "newmain" stack onto the finalList
          while(!copyStack.empty()) {
            finalList.push_front(copyStack.top());
            copyStack.pop();
          }
          // outputting into the file
          for (iter = finalList.begin(); iter != finalList.end(); ++iter) {
            outFS << *iter << " ";
          }
          outFS << endl;
          outFS.close();
          return;
        }
        else {
          queueStack.push(copyStack);
          iter = dict.erase(iter);
        }
      }
      else {
        iter++;
      }
    }
    queueStack.pop();
    if(queueStack.empty()){
      outFS << "No Word Ladder Found." << endl;
    }
  }
  outFS.close();
  return;
}