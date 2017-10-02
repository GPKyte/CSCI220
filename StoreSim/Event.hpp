// Gavin Kyte
// Thu Sep 28 16:31:27 2017
#pragma once
#include <utility> // So to only overload operations < and ==
#include "Customer.hpp"
enum EventType {Arrival, EndShopping, EndCheckout};

class Event {
private:

public:
  EventType type;
  double simTime;
  Customer person;
  Event(EventType e, double simTime, Customer cust) {
    type = e;
    this->simTime = simTime;
    person = cust;
  }
  friend bool operator<(const Event& a, const Event& b) {
    return a.simTime < b.simTime;
  }
  friend bool operator>(const Event& a, const Event& b) {
    return a.simTime > b.simTime;
  }
  friend bool operator>=(const Event& a, const Event& b) {
    return a.simTime >= b.simTime;
  }
  friend bool operator<=(const Event& a, const Event& b) {
    return a.simTime <= b.simTime;
  }
  friend bool operator!=(const Event& a, const Event& b) {
    return a.simTime != b.simTime;
  }
  friend bool operator==(const Event& a, const Event& b) {
    return a.simTime == b.simTime;
  }
};
