// basic file operations
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Customer.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "RegisterQueue.h"
using namespace std;

class StoreSimulator{

private:
  PriorityQueue<Event> events;
  vector<RegisterQueue> registers;
  double simClock;

public:
  StoreSimulator(){
    simClock = 0;
  }

  void startSimulation(int numNormal, int numSelfScan) {
    loadRegisters(numNormal, numSelfScan);
    loadCustomerData();

    while(events.size > 0){
      Event e = events.dequeue();
      simClock = e.simTime;
      if(e.type == EventType::Arrival){
        handleArrival(e);
      }else if(e.type == EventType::EndShopping){
        handleEndShopping(e);
      }else{
        handleEndCheckout(e);
      }
    }
  }

  void loadCustomerData(){
    double simClock, avgSelectionTime;
    int items;

    ifstream myfile ("arrival.txt");
    if (myfile.is_open()){
      while (myfile >> simTime >> items >> avgSelectionTime){

        Customer cust(simClock, items, avgSelectionTime) ;
        cout << cust << endl;
        Event e(EventType::Arrival, simClock, cust);
        events.enqueue(e);
      }
      myfile.close();
    }else
    throw(1);

  }

  void loadRegisters(int numNormal, int numSelfScan){
    for(int i = 0; i < numNormal; i ++){
      RegisterQueue r(1.5, .01);
      registers.push_back(r);
    }
    for(int i = 0; i < numSelfScan; i++){
      RegisterQueue r(3.0, .04);
      registers.push_back(r);
    }
  }

  void handleArrival(Event& e){
    Customer c = e.person;
    double finishShopping = c.getCustomerArrival() + (c.getOrderSize() * c.getTimeToGetItem());
    Event next(EventType::EndShopping, finishShopping, c);
    events.enqueue(next);
  }

  void handleEndShopping(Event& e){
    Customer c = e.person;
    // Find lane with least # of people
    int min = 0;
    for (int i = 1; i < registers.size(); i++) {
      if (registers[i].numberOfCustomers < registers[min].numberOfCustomers)
        min = i;
    }
    RegisterQueue r = registers[min];
    c.chooseRegister(min);
    if(r.numberOfCustomers == 0) {
      double finishCheckout = r.minToPay + (c.getOrderSize() * r.minPerItem);
      Event next(EventType::EndCheckout, finishCheckout, c);
      events.enqueue(next)
    }
    // If waiting in line, their EndCheckout is scheduled once they are up
    r.enqueue(c);
  }

  void handleEndCheckout(Event& e){
    Customer current = e.person;
    RegisterQueue r = registers[current.getRegister()];
    r.dequeue();
    Customer c = r.seeNext();
    double finishCheckout = r.minToPay + (c.getOrderSize() * r.minPerItem);
    Event next(EventType::EndCheckout, finishCheckout, c);
    events.enqueue(next);
  }
};
