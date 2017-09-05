// Class on Tuesday the 9th
// Author: Gavin Kyte
// Class: CSCI 220 Data Structures and Algorithms

#include <iostream>
#include <iomanip>
#include "BetterArray.h"
using namespace std;

// Questions for Quiz:
  // Fill in a prototype method
  // Know whether a parameter is passed by reference or value
  // "new" and "delete" relationship

int main(){
  BetterArray a;
  BetterArray b(5);
  BetterArray * c;
  c = new BetterArray(8);
  a[0] = 7;
  cout << a[0] << endl;
  return 0;
}
