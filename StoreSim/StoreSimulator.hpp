// basic file operations
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Customer.hpp"
#include "Event.hpp"
#include "PriorityQueue.hpp"
#include "RegisterQueue.hpp"
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
      while (myfile >> simClock >> items >> avgSelectionTime){
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
    cout << "Customer " << c << " started shopping at " << finishShopping << endl;
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
      cout << "Customer " << c << " checking out at " << finishCheckout << endl;
      Event next(EventType::EndCheckout, finishCheckout, c);
      events.enqueue(next);
    }
    // If waiting in line, their EndCheckout is scheduled once they are up
    r.enqueue(c);
    cout << "Customer " << c << " waiting in line " << min << endl;
  }

  void handleEndCheckout(Event& e){
    Customer current = e.person;
    int lane = current.getRegister();
    RegisterQueue r = registers[lane];
    cout << "Customer " << current << " finished checking out from register " << lane << endl;
    try {
      r.dequeue();
    } catch(int e) {
      cout << "register was empty (caught error). Moving on." << endl;
    }
    if (r.numberOfCustomers > 0) {
      Customer c = r.seeNext();
      double finishCheckout = r.minToPay + (c.getOrderSize() * r.minPerItem);
      cout << "Customer " << c << " checking out at " << finishCheckout << endl;
      Event next(EventType::EndCheckout, finishCheckout, c);
      events.enqueue(next);
    }
  }
};
