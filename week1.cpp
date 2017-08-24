//Week 1A
// Gavin Kyte
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

// JAVA has true and false
// C++ has 0 and !0
int main() {
  std::cout << "Hello World" << std::endl;
  // system("pause");
  int i = 5;
  float f = .6;
  double d = .445;

  cout << setw(5) << i << setw(5) << f << setw(7) << d << endl;
  if (10){
    cout << "YES!" << endl;
  }


  return 0;
}
