#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
    Node* temp = new Node;
    temp->payload = payload;
    return temp;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    
    Node* prev = nullptr;
    string name;

    Node* curr = head;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        if (head == nullptr) {
            head = newNode(name); // initialize head specially
            head->next = newNode(name);
            curr = head->next;
        }
        else { 
          delete curr;
          curr = newNode(name);
          prev = curr;
          curr->next = newNode(name);
          curr = curr->next;
        }
      
    }

    if (prev != nullptr) { // make circular
        delete curr;
        prev->next = head;
    }
    
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    cout << curr->payload << endl;
    curr = curr->next;
    while (curr != nullptr && curr != start) {
        cout << curr->payload << endl;
        curr = curr->next;
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr != curr->next) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
          prev = curr;
          curr = curr->next;
        }
        prev->next = curr->next; // delete kth node
        delete curr; 
        curr = prev->next;
    }

    return curr; // last person standing
}

/*
runGame(start,1)
curr = a
prev = a
curr = b
a->next = c
delete b
curr = c
*/


/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1), removed "max"
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input
    // initialize and run game
    Node* startPerson = loadGame(n, names);
    cout << endl;
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}
