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
      myfile.clear();
      myfile.seekg(0, myfile.beg);
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

    // Calculate wait time = EndCheckout - (arrival + shopTime + checkoutTime) = EndCheckout - EndShopping
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
    cout << "Avg wait: " << avgWait << " minutes" << endl;

    cout << "Max line for each register: " << '[' << registers[0].maxLineLength;
    int maxLineLength = registers[0].maxLineLength;
    for(int i = 1; i < registers.size(); i++) {
      cout << ", " << registers[i].maxLineLength;
      if(registers[i].maxLineLength > maxLineLength)
        maxLineLength = registers[i].maxLineLength;
    }
    cout << "]" << endl;
    cout << "Most in line at once: " << maxLineLength << endl;
    cout << "Total for each register: ";
    int total = 0;
    cout << '[';
    for(int i = 0; i+1 < registers.size(); i++) {
      cout << registers[i].totalCount << ", ";
      total += registers[i].totalCount;
    }
    cout << registers[registers.size()-1].totalCount << ']' << endl;
    total += registers[registers.size()-1].totalCount;

    cout << "Total customers: " << total << endl;
    waitTimes.clear();
    registers.clear();
  }
};
