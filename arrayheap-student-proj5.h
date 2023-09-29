/**
* file: arrayheap-student-proj5.h
* author: Michael Mathews
* course: CSI 3334
* assignment: project 5
* due date: April 8, 2022
* version: 11.7
 
 This file defines the arrayHeap class and its functions
*/

#ifndef ARRAYHEAP_STUDENT_PROJ5_H
#define ARRAYHEAP_STUDENT_PROJ5_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/* ArrayHeap default constructor
*  parameters:
*      none
*  return value: none
*
* This function creates the base ArrayHeap
*/
template <class T>
ArrayHeap<T>::ArrayHeap(){
    this->numItems = 0;
    this->capacity = 5;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    //initialize free stack
    for(int i = 0; i < this->capacity; i++){
        this->heapAndFreeStack[i] = i;
    }
}

/* ArrayHeap copy constructor
*  parameters:
*      none
*  return value: none
*
* This function copies an ArrayHeap
*/
template <class T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h){
    //deep copy data members
    this->numItems = h.numItems;
    this->capacity = h.capacity;
    this->data = new T[h.capacity];
    this->heapAndFreeStack = new int[h.capacity];
    for(int i = 0; i < h.capacity; i++){
        this->data[i] = h.data[i];
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}
 
/* ArrayHeap destructor
*  parameters:
*      none
*  return value: none
*
* This function deletes an ArrayHeap
*/
template <class T>
ArrayHeap<T>::~ArrayHeap(){
    delete [] this->data;
    this->data = nullptr;
    delete [] this->heapAndFreeStack;
    this->heapAndFreeStack = nullptr;
}

/* insert
*  parameters:
*      item - thing to be inserted
*  return value: none
*
* This function inserts an item to the ArrayHeap
*/
template <class T>
void ArrayHeap<T>::insert(T const &item){
    //make sure there is room to insert
    if(this->numItems == this->capacity){
        this->doubleCapacity();
    }
    //get next index from free stack and store item there
    this->numItems++;
    this->data[heapAndFreeStack[numItems-1]] = item;
    bubbleUp(numItems-1);
}

/* removeMinItem
*  parameters:
*      none
*  return value: none
*
* This function removes the highest priority item from an ArrayHeap
*/
template <class T>
void ArrayHeap<T>::removeMinItem(){
    const int FIRST = 0;
    //make sure there is an item to remove
    if(this->numItems > 0){
        //bring last element to front and decrement size
        swap(heapAndFreeStack[0],heapAndFreeStack[numItems-1]);
        this->numItems--;
        //bubble down first index
        bubbleDown(FIRST);
    }
}

/* operator=
*  parameters:
*      none
*  return value: none
*
* This function allows for the = operator to be used on ArrayHeaps
*/
template <class T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah){
    //make sure not the same; copy data and heap
    if(this != &ah){
        //deallocate memory
        delete [] this->data;
        delete [] this->heapAndFreeStack;
        //deep copy data members
        this->numItems = ah.numItems;
        this->capacity = ah.capacity;
        this->data = new T[this->capacity];
        this->heapAndFreeStack = new int[this->capacity];
        for(int i = 0; i < ah.capacity; i++){
            this->data[i] = ah.data[i];
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        }
    }
    return *this;
}

/* doubleCapacity
*  parameters:
*      none
*  return value: none
*
* This function doubles the capacity of an ArrayHeap
*/
template <class T>
void ArrayHeap<T>::doubleCapacity(){
    //make a larger heapAndFreeStack and data
    int initCap = this->capacity;
    this->capacity *= 2;
    T *tempData = new T[this->capacity];
    int *tempHeap = new int[this->capacity];
    //initialize free stack
    for(int i = 0; i < this->capacity; i++){
        tempHeap[i] = i;
    }
    //copy data members to larger array
    for(int i = 0; i < initCap; i++){
        tempHeap[i] = this->heapAndFreeStack[i];
        tempData[i] = this->data[i];
    }
    //delete original arrays
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    //set implicit data and heap to larger arrays
    this->data = tempData;
    this->heapAndFreeStack = tempHeap;
}

/* getMinItem
*  parameters:
*      none
*  return value: templated item from the top of the heap
*
* This function returns the highest priority item from an ArrayHeap
*/
template <class T>
T const &ArrayHeap<T>::getMinItem() const{
    return this->data[heapAndFreeStack[0]];
}

/* getNumItems
*  parameters:
*      none
*  return value: integer that represents the number of items in an ArrayHeap
*
* This function returns the number of items in an ArrayHeap
*/
template <class T>
int ArrayHeap<T>::getNumItems() const{
    return this->numItems;
}

/* bubbleUp
*  parameters:
*      ndx - index in the arrayHeap that points to the data to be bubbled up
*  return value: none
*
* This function bubbles up an item in an ArrayHeap until in the right location
*/
template <class T>
void ArrayHeap<T>::bubbleUp(int ndx){
    bool done = false;
    while(!done){
        //find parent
        int parent = (ndx-1) / 2;
        //make sure not first item
        if(ndx > 0){
            if(data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]){
                swap(heapAndFreeStack[parent], heapAndFreeStack[ndx]);
                ndx = parent;
            }
            //process is where it should be
            else{
                done = true;
            }
        }
        //no parent
        else{
            done = true;
        }
    }
}

/* bubbleDown
*  parameters:
*      ndx - index in the arrayHeap that points to the data to be bubbled down
*  return value: none
*
* This function bubbles down an item in an ArrayHeap until in the right location
*/
template <class T>
void ArrayHeap<T>::bubbleDown(int ndx){
    int child1, child2;
    bool done = false;
    
    while(!done){
        child1 = ndx*2 + 1;
        child2 = ndx*2 + 2;
        //check if viable 2 children valid
        if(child2 < this->numItems){
            //check if a child is less than the current value
            if(data[heapAndFreeStack[child1]] < data[heapAndFreeStack[ndx]] or
               data[heapAndFreeStack[child2]] < data[heapAndFreeStack[ndx]]){
                //check which child is smaller
                //if child 1 is smaller than child 2, swap it, else swap child2
                if(data[heapAndFreeStack[child1]] <
                   data[heapAndFreeStack[child2]]){
                    swap(heapAndFreeStack[child1], heapAndFreeStack[ndx]);
                    ndx = child1;
                }
                else{
                    swap(heapAndFreeStack[child2], heapAndFreeStack[ndx]);
                    ndx = child2;
                }
            }
            else{
                done = true;
            }
        }
        //if only one viable child
        else if(child1 < this->numItems){
            //if child 1 is smaller, swap it, else swap child2
            if(data[heapAndFreeStack[child1]] < data[heapAndFreeStack[ndx]]){
                swap(heapAndFreeStack[child1], heapAndFreeStack[ndx]);
                ndx = child1;
            }
            else{
                done = true;
            }
        }
        //no children
        else{
            done = true;
        }
    }
}
                        
#endif
