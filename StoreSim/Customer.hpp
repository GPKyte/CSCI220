// Gavin Kyte
// Thu Sep 28 16:32:09 2017
#pragma once

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
  ~Customer() {delete(this);}
  void chooseRegister(int num) {registerNum = num;}
  int getRegister() {return registerNum;}
  int getOrderSize() {return items;}
  double getCustomerArrival() {return simClock;}
  double getTimeToGetItem() {return avgSelectionTime;}
};
