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
  vector<double> waitTimes;
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
    endSimulation();
  }

  void loadCustomerData(){
    double simClock, avgSelectionTime;
    int items;

    ifstream myfile ("arrival.txt");
    if (myfile.is_open()){
      while (myfile >> simClock >> items >> avgSelectionTime){
        Customer cust(simClock, items, avgSelectionTime) ;
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
    RegisterQueue *r = &registers[min];
    c.chooseRegister(min);
    r->enqueue(c);
    // If waiting in line, their EndCheckout is scheduled once they are up
    if(r->numberOfCustomers <= 1) {
      double finishCheckout = e.simTime + r->minToPay + (c.getOrderSize() * r->minPerItem);
      Event next(EventType::EndCheckout, finishCheckout, c);
      events.enqueue(next);
    }
  }
  void handleEndCheckout(Event& e){
    Customer out = e.person;
    int lane = out.getRegister();
    RegisterQueue *r = &registers[lane];

    // Calculate wait time = EndCheckout - (arrival + shopTime + checkoutTime)
    double wait = e.simTime // EndCheckout
                  - (out.getCustomerArrival() // arrival
                     + (out.getOrderSize() * out.getTimeToGetItem()) // shopTime
                     + r->minToPay + (out.getOrderSize() * r->minPerItem)); // checkoutTime
    waitTimes.push_back(wait);

    // Let person leave simulation
    try {
      r->dequeue();
    } catch(char const* e) {
      cout << "- Caught eror: " << e << endl;
    }
    // Check out next person in line
    if (r->numberOfCustomers > 0) {
      Customer c = r->seeNext();
      double finishCheckout = e.simTime + r->minToPay + (c.getOrderSize() * r->minPerItem);
      Event next(EventType::EndCheckout, finishCheckout, c);
      events.enqueue(next);
    }
  }
  void endSimulation() {
    double avgWait = 0;
    for(int i = 0; i < waitTimes.size(); i++) {
      avgWait += waitTimes[i];
    }
    avgWait /= waitTimes.size();
    cout << "Average wait time was " << avgWait << endl;
    int maxLineLength = registers[0].maxLineLength;
    for(int i = 1; i < registers.size(); i++) {
      if(registers[i].maxLineLength > maxLineLength)
        maxLineLength = registers[i].maxLineLength;
    }
    cout << "Most customers in line at once " << maxLineLength << endl;
  }
};
