// Gavin Kyte
// Mon Sep 11 08:45:00 2017

#include <iostream>
#include <iomanip>
#include "MagicBag.h"
using namespace std;

int main(){
  MagicBag bag;

  bag.insert(2);
  bag.insert(50);
  bag.insert(9);
  cout << bag.draw() << endl;
  cout << bag.peek(9) << endl;
  bag.print();
  return 0;
}
