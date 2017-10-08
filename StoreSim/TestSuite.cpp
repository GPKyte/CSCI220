// Gavin Kyte
// Fri Oct  6 16:57:17 2017

// basic file operations
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Customer.hpp"
#include "Event.hpp"
#include "PriorityQueue.hpp"
#include "RegisterQueue.hpp"
#include "StoreSimulator.hpp"
using namespace std;

int main(){
  cout << "Test Customer" << endl;
  Customer c(385.71, 113, 0.28);
  cout << "Pre-register select: "<< c.getRegister() << endl;
  c.chooseRegister(5);
  cout << "Post-register select: " << c.getRegister() << endl;
  cout << "Arrival time: " << c.getCustomerArrival() << endl;
  cout << "Order size: " << c.getOrderSize() << endl;
  cout << "Selection speed: " << c.getTimeToGetItem() << endl;
  cout << "Print << result: " << c << endl;
  cout << "Test copy Customer c2" << endl;
  Customer c2(c);
  cout << c2 << endl;

  cout << "Test Event" << endl;
  Event e1(EventType::Arrival, 100.00, c);
  Event e2(EventType::EndShopping, 200.00, c);
  cout << "e1 is type " << e1.type << ", e2 is type " << e2.type << endl;
  cout << "e1 time is " << e1.simTime << ", e2 time is " << e2.simTime << endl;
  cout << "e1 < e2  " << (e1 < e2) << endl;
  cout << "e1 > e2  " << (e1 > e2) << endl;
  cout << "e1 >= e2  " << (e1 >= e2) << endl;
  cout << "e1 <= e2  " << (e1 <= e2) << endl;
  cout << "e1 == e2  " << (e1 == e2) << endl;
  cout << "e1 != e2  " << (e1 != e2) << endl;
  cout << "Testing PriorityQueue" << endl;
  PriorityQueue<int> pq;
  pq.enqueue(1);
  pq.enqueue(2);
  pq.enqueue(2);
  pq.enqueue(3);
  cout << pq.dequeue() << endl;
  cout << pq.dequeue() << endl;
  cout << pq.dequeue() << endl;
  cout << pq.dequeue() << endl;
  try {
    cout << pq.dequeue() << endl;
  } catch(char const* e) {
    cout << "Dequeue when empty gives: " << e << endl;
  }

  pq.enqueue(5);
  pq.enqueue(3);
  pq.enqueue(3);
  pq.enqueue(1);
  pq.enqueue(6);
  pq.enqueue(3);
  pq.enqueue(2);
  pq.enqueue(8);
  while(true) {
    try {
      cout << pq.dequeue() << endl;
    } catch(char const* e) {
      cout << "Reached end of list" << endl;
      break;
    }
  }
  cout << "Testing RegisterQueue" << endl;
  RegisterQueue rq(1.0, .1);
  rq.enqueue(Customer(385.71, 115, 0.82));
  rq.enqueue(Customer(30.71, 10, 0.127));
  rq.enqueue(Customer(85.71, 130, 0.2));
  rq.enqueue(Customer(485.10, 83, 0.289));
  cout << rq.dequeue() << endl;
  cout << rq.dequeue() << endl;
  cout << rq.dequeue() << endl;
  cout << rq.dequeue() << endl;
  try {
    cout << rq.dequeue() << endl;
  } catch(char const* e) {
    cout << "Dequeue when empty gives: " << e << endl;
  }
  // To test this section, uncomment code and change the input file
  // in StoreSimulator from "arrival.txt" to "testData.txt"
  // cout << "In test data 10 identical customers enter at same time and all go in one line" << endl;
  // StoreSimulator s;
  // 1.5 min to pay, .1 min per item.
  // Average wait = first + last / 2 = (0 + 9*(1.5 + 10 .01))/2 = 7.2 min
  // s.startSimulation(1,0);
  // s.startSimulation(0,1); // 3.0, .04
}
