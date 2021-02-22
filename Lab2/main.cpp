
#include <iostream>

#include "IntList.h"

using namespace std;

int main() {
  IntList Test;
    


    
  // Test.push_front(3);
  // cout << "Ordered: " << Test << endl;
  // cout << "Reverse: "; Test.printReverse(); cout << endl;
  // Test.push_back(1);
  // cout << "Ordered: " << Test << endl;
  // cout << "Reverse: "; Test.printReverse(); cout << endl;
  // Test.push_back(5);
  // cout << "Ordered: " << Test << endl;
  // cout << "Reverse: "; Test.printReverse(); cout << endl;
  // Test.push_front(2);
  // cout << "Ordered: " << Test << endl;
  // cout << "Reverse: "; Test.printReverse(); cout << endl;
  // Test.pop_back();
  // cout << "after pop back Ordered: " << Test << endl;
  // cout << "Reverse: "; Test.printReverse(); cout << endl;

  // Test.pop_front(); // messes up reverse
  // cout << "Ordered: " << Test << endl;
  // cout << "Reverse: "; Test.printReverse(); cout << endl;
  // cout << endl;

  // Test.push_back(3);
  // cout << Test << endl;
  // Test.push_back(8);
  // cout << Test << endl;
  // Test.push_back(12);
  // cout << Test << endl;
  // Test.pop_back();
  // cout << Test << endl;
  // Test.pop_back();
  // cout << Test << endl;
  // Test.pop_back();
  // cout << Test << endl;

  Test.push_front(1);
  cout << Test << endl;
  Test.push_back(2);
  cout << Test << endl;
  Test.printReverse();
  cout << endl;
  Test.pop_front();
  cout << Test << endl;
  Test.pop_front();
  cout << Test << endl;



  return 0;
}
