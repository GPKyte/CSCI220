// Week 2A
// Gavin Kyte

#include <iostream>
#include <iomanip>
using namespace std;

// returnType, MethodName(paramType, [paramType,...]);
// template, <class T> T MethodName(T, [T,...]);    T == var for "type"
template <class T> T getValueInRange(T, T);

int main() {
  int i = 12;
  // Pointer to type "int" p = the memory location of i
  int * p = &i; // * is pointer, & is memory location
  //?? hmm not sure here
  int & r = i;

  // "Go to this pointer location and assign value 54 to it"
  *p = 54;

  cout << i << endl;
  cout << hex << p << dec << endl;
  cout << r << endl;
  cout << * p << endl;
  return 0;
}
