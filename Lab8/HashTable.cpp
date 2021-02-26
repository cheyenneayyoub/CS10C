#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
	size = s;
  hashTable = new list<WordEntry>[s];
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
  int num = 0;
  for(unsigned int i = 0; i < s.size(); ++i){
    num = num + static_cast<int>(s.at(i));
    num = num * (i+1);
    num = num % size;
  }
  return num;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/

/*
HashInsert(hashTable, item) {
   // Hash function determines initial bucket
   bucket = Hash(item.key)    
   bucketsProbed = 0
   N = hashTable's size
   while (bucketsProbed < N) {
      // Insert item in next empty bucket
      if (hashTable[bucket] is Empty) {
         hashTable[bucket] = item
         return true 
      }

      // Increment bucket index
      bucket = (bucket + 1) % N

      // Increment number of buckets probed
      ++bucketsProbed
   }

   return false      
}*/
void HashTable::put(const string &s, int score) {
	int bucket = computeHash(s);
  // int bucketsProbed = 0;
  // int n = size;
  // while(bucketsProbed < n) {
  //   if(hashTable[bucket] != 0) {
  //     hashTable[bucket] = item;
  //     return;
  //   }
  //   bucket = (bucket + 1) % n;
  //   ++bucketsProbed;
  // }
  // return;
  list<WordEntry>::iterator i;
  if(contains(s)){
    for(i = hashTable[bucket].begin(); i != hashTable[bucket].end(); i++){
      if(i->getWord() == s){
        i->addNewAppearance(score);
        return;
      }
    }
    
  }
  else{
    WordEntry word = WordEntry(s, score);
    hashTable[bucket].push_back(word);
  }
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
  int index = computeHash(s);
  list<WordEntry>::iterator i;
  for(i = hashTable[index].begin(); i != hashTable[index].end(); i++){
    if(s == i->getWord()){
      return i->getAverage();
    }
  }
  return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
  int index = computeHash(s);
  list<WordEntry>::iterator i;
  for (i = hashTable[index].begin(); i != hashTable[index].end(); i++){
    if (s == i->getWord()){
      return true;
    }
  }
  return false;
}

