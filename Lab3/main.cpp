
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
using namespace std;

vector<char> createVector();

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

template<typename T>
void selection_sort(vector<T> &vals);

template<typename T>
T getElement(vector<T> vals, int index);

int main() {
  cout << "UNSORTED: ";

  vector<string> test;
  test.push_back("apple");
  test.push_back("Apple");
  test.push_back("bear");
  test.push_back("zebra");
  for(unsigned int i = 0; i < test.size(); i++){
      cout << test.at(i) << " ";
  }

  cout << endl << "SORTED: ";
  selection_sort(test);
  for(unsigned int i = 0; i < test.size(); i++){
      cout << test.at(i) << " ";
  }
  cout << endl;

    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    unsigned int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
      cout << "Size: " << vals.size() << endl;
      cout << "Enter a number: " << endl;
      cin >> index;
      try{
        // if(index < 0 || index >= vals.size()) { 
        //   throw out_of_range("Not in range");
        // }
       curChar = getElement(vals,index);
       cout << "Element located at " << index << ": is " << curChar << endl;
      }
      catch(out_of_range &excpt){
        cout << "out of range exception occured" << endl;
        return 0;
      }
    }

  return 0;
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
  T min = vals.at(index);
  for(unsigned int i = index; i < vals.size(); i++) {
    if(vals.at(i) < min){
      min = vals.at(i);
      index = i;
    }
  }
  return index;
}

template<typename T>
void selection_sort(vector<T> &vals) { 
  for(unsigned i = 0; i < vals.size(); i++){
    unsigned minIndex = min_index(vals, i);
    T temp = vals.at(i);
    vals.at(i) = vals.at(minIndex); 
    vals.at(minIndex) = temp;
  }
}

template<typename T>
T getElement(vector<T> vals, int index) {
  return vals.at(index);
}

