// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************

};

// ***************************************
// Templated function definitions go here!
// ***************************************

//Heap constructor
//sets variables and creates a heap
template <class T>
Heap<T>::Heap() {
  //i create a fake data value that goes into the 0 index to make
  //sure that the 0 index is never used. Marron said it was okay 
  _used = false;
  T data;
  _heap = {};
  _heap.push_back(data);

}
//insert
//inserts a T object into the heap
template <class T>
void Heap<T>::insert(const T& object) {
  //get size of heap and subtract 1 
  int size = _heap.size() - 1;
  //push back if empty
  if(size == 0) {
    _heap.push_back(object);
  
  }
  else {
    //push back object
    _heap.push_back(object);
    size = size + 1;
    
    //heapifyUp basically
    //gets the parent and the current position of the current object
    int parent = size / 2;
    int position = size;
    
    //checks the priorities and if the position is not the root 
    while(_heap.at(parent).priority() < _heap.at(position).priority() and position != ROOT) {
      //if so, swap and keep attempting to heapify
      swap(_heap.at(parent), _heap.at(position));
      position = parent;
      parent = position / 2;
    }
  }
  //sets used to true 
  _used = true;
}

//readTop
//returns the top value of the heap
template <class T>
T Heap<T>::readTop() const {
  //if heap is empty, throw an error 
  if(empty()) {
    throw range_error("Empty heap");
  }
  //returns the root value
  else {
    return _heap.at(ROOT);
  }
}

//removeTop
//removes the top node in the heap 
template <class T>
void Heap<T>::removeTop() {
  //if the heap is empty throw an error 
  if(empty()) {
    throw range_error("Empty Heap");
  }
  else {
    //gets the size 
    int size = _heap.size() - 1;
    //swaps the last node with the root
    _heap.at(ROOT) = _heap.back();
    //deletes the node that was the root
    _heap.pop_back();

    //variable to get the highest priority
    int top = ROOT;

    //while the top is the root (should run at least once)
    while(top == ROOT) {
      //left and right children
      int left = ROOT * 2;
      int right = (ROOT * 2) + 1;

      //if the left has a higher priority set top to left child
      if(left < size and _heap.at(left).priority() > _heap.at(ROOT).priority()) {
	top = left;
      }

      //if the right has a higher priority, set top to right child
      if(right < size and _heap.at(right).priority() > _heap.at(top).priority()) {
	top = right;
      }
      //if the top does not equal the root anymore then swap the values
      if(top != ROOT) {
	swap(_heap.at(ROOT), _heap.at(top));
	//sets the top equal to the new root and does it again
	top = ROOT;
      }
      //if nothing can change anymore then break
      else {
	break;
      }
    }
  }
 }

//dump
//dumps the contents of the heap 
template <class T>
void Heap<T>::dump() const {
  //for loop that goes through the heap and prints the data 
  for(unsigned int i = 1;  i < _heap.size(); i++) {
    cout << _heap.at(i) << endl;
  }


}


#endif
