// Class on Tuesday the 9th
// Author: Gavin Kyte
// Class: CSCI 220 Data Structures and Algorithms

#include <iostream>
#include <iomanip>
#include "BetterArray.h"
#include <vector>
using namespace std;

// Questions for Quiz:
  // Fill in a prototype method
  // Know whether a parameter is passed by reference or value
  // "new" and "delete" relationship

int main(){
  vector<int> v(10);
  v[0] = 6;
  v.resize(20);   // Resizes the array and keeps data
  v.size();       // Show size
  v.push_back(6); // Appends parameter to end of array and extends
  int a[5];
  cout << sizeof(a)/sizeof(a[0]) << endl;
  return 0;
}
