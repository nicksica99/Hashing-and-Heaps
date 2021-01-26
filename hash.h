// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

//HashTable constructor
//creates the hashtable
template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash) {
  //sets variables
  _N = size;
  _n = 0;
  _hash = hash;
  //creates the hashtable
  _table = new Heap<T>[_N];
  
}
//Destructor
//deallocates the hashtable
template <class T>
HashTable<T>::~HashTable() {
  //delete and set to nullptr
  delete [] _table;
  _table = nullptr;

}
//Copy Constructor
//creates a deep copy of the hash table
template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht) {
  //creates a new copy of the hashtable 
  _table = new Heap<T>[ht.tableSize()];
  //sets the variables 
  _n = ht.numEntries();
  _N = ht.tableSize();
  _hash = ht._hash;
  //puts all of the data into the new table
  for(unsigned int i = 0; i < _N; i++) {
    _table[i] = ht._table[i];
  }
  
}
//Assignment Operator
//creates a deep copy of the hashtable 
template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht) {
  //protect from self-assignment
  if(this == &ht) {
    return *this;
  }
  //deletes current object table
  delete [] _table;
  //creates a deep copy of the table and sets variables 
  _table = new Heap<T>[ht.tableSize()];
  _n = ht.numEntries();
  _N = ht.tableSize();
  _hash = ht._hash;
  //puts all of the data into the new table 
  for(unsigned int i = 0; i < _N; i++) {
    _table[i] = ht._table[i];
  }

  return *this;

}
//insert
//inserts T objects into the hash table 
template <class T>
bool HashTable<T>::insert(const T& object) {
  //varaibles 
  bool vacant = false;
  string type = object.key();
  //gets hash value
  unsigned int hash = _hash(type);
  hash = hash % _N;

  //index for the loop
  unsigned int index = hash;
  //if the table is full
  if(_n == _N) {
    return false;
  }
  //while it hasnt found a vacant spot 
  while(vacant == false) {
    //if the index has been used but it is empty
    if(_table[index].used() == true and _table[index].size() == 0) {
       _table[index].insert(object);
       vacant = true;
    }
    //if the index has been used and the key is the same then it inserts it into the heap
    else if(_table[index].used() == true and _table[index].readTop().key() == type) {
      _table[index].insert(object);
      vacant = true; 
    }
    //if the index has not been used then it inserts it into the heap
    else if(_table[index].used() == false) {
      _table[index].insert(object);
      //increases the number of entries 
      _n++;
      vacant = true;
    }
    
    else {
      //if the index reaches the end of the array it sends it to the start
      if(index == _N) {
	index = 0;
      }
      else {
	//increments index
	index++;
      }
    }
  }
  return true;
}
//getNext
//finds the correct hash, reads it, and removes it
template <class T>
bool HashTable<T>::getNext(string key, T& obj) {
  //for loop that goes through the table
  for(unsigned int i = 0; i < _N; i++) {
    //if the index has been used
    if(_table[i].used() == true) {
      //checks if the table size is 0, which if it is it just skips it
      //this handles if there were objects in the heap that have been removed to make it empty
      if(_table[i].size() == 0) {
	continue;
      }
      //if correct key, then remove the top 
      else if(_table[i].readTop().key() == key) {
	obj = _table[i].readTop();
	_table[i].removeTop();

	//reduces the number of entries if the index of the hash is now empty
	if(_table[i].empty() == true) {
	  _n--;
	}
	return true;
      }
    }
    
  
  }
  
  return false;
}

//dump
//dumps the hash table
template <class T>
void HashTable<T>::dump() const {
  //for loop that goes through the hash table and calls the heap dump function
  for(unsigned int i = 0; i < _N; i++) {
    cout << "[" << i << "]:" << endl;
    _table[i].dump();
  }


}

#endif
