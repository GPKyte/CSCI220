// Week 2A
// Gavin Kyte

#include <iostream>
#include <iomanip>
using namespace std;

void swap(int * a, int *b);
int main() {
  int a = 12;
  int b = 14;

  // cpp assumes you want to copy everything
  cout << a << " " << b << endl;
  swap(&a, &b);
  cout << a << " " << b << endl;
  return 0;
}

void swap(int * a, int * b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
