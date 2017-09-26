// Gavin Kyte
// Thu Sep 21 13:08:42 2017

#include <iostream>
#include <iomanip>
using namespace std;

enum EventType = { ARRIVAL, END_CHECKOUT, END_SHOPPING };

class Event {
  EventType t = EventType.ARRIVAL;
}

// FIFO = queue
// FILO = stack
// Stack can be implemented with LList, better than array
// Stacks are fast, easy, and typically used in OS's and for returning from methods.
// Every thread has it's own stack

// Stacks can run out of memory and throw error
// Two stacks in a program can be used. Let them 'grow' toward eachother.
