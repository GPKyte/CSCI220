// Gavin Kyte
// Thu Sep 28 16:32:09 2017
#pragma once
#include <iostream>
#include <iomanip>

class Customer {
private:
  double simClock;
  int items;
  double avgSelectionTime;
  int registerNum;

public:
  Customer() {
    simClock = items = avgSelectionTime = 0;
    registerNum = -1;
  }
  Customer(double simClock, int items, double avgSelectionTime) {
    this->simClock = simClock;
    this->items = items;
    this->avgSelectionTime = avgSelectionTime;
    registerNum = -1;
  }
  ~Customer() {}
  void chooseRegister(int num) {registerNum = num;}
  int const getRegister() {return registerNum;}
  int const getOrderSize() {return items;}
  double const getCustomerArrival() {return simClock;}
  double const getTimeToGetItem() {return avgSelectionTime;}
  friend std::ostream& operator<<(std::ostream& os, const Customer& c) {
    std::cout << '[' << c.simClock << ", " << c.items << ", "
      << c.avgSelectionTime << ", " << c.registerNum << ']';
    return os;
  }
};
