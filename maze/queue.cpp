/*
 queue.cpp
 
 Author: Josie Jitzel Alvarez
 
 Short description of this file:
 
 Adds/removes locations in the queue
 
 */

#include "queue.hpp"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
    contents = new Location[maxlen];
    head = 0;
    tail = 0;
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
    delete[] contents;
}

// insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {
    contents[tail] = loc;               //updates the back of the list
    tail++;                             //increments tail to
    //insert another location
    //at the back if needed
    
}

// return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
    
    return contents[head++];        //returns the oldest location
    //increments head to move to new head
    //in list (i.e. next oldest location)
    
}


// is this Queue empty? (did we extract everything added?)
// this is complete, you don't need to change it.
bool Queue::is_empty() {
    return head == tail;
}

