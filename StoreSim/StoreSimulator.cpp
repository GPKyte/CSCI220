// basic file operations
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Customer.cpp"
#include "Event.cpp"
#include "PriorityQueue.cpp"
#include "RegisterQueue.h"
using namespace std;

class StoreSimulator{

private:
  MyPriorityQueue<Event> events;
  vector<RegisterQueue> registers;
  double simClock;

public:
  StoreSimulator(){
    simClock = 0;
  }

  void startSimulation() {
    loadRegisters( 6, 4);
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
      while ( myfile >> simTime >> items >> avgSelectionTime){

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

  }

  void handleEndCheckout(Event& e){

  }


};
