// Gavin Kyte
// Thu Sep 28 16:31:27 2017
#pragma once
#include <utility> // So to only overload operations < and ==
#include "Customer.h"
enum EventType {Arrival, EndShopping, EndCheckout};

class Event {
private:

public:
  EventType event;
  double simTime;
  Customer person;
  Event(EventType e, double simTime, Customer cust) {
    event = e;
    this->simTime = simTime;
    person = cust;
  }
  bool operator<(Event& e const) {
    return this->simTime < e.simTime;
  }
  bool operator==(Event& e const) {
    return this->simTime == e.simTime;
  }
};
