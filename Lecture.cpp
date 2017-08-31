// Week 2A
// Gavin Kyte

#include <iostream>
#include <iomanip>
#include "./student.h"

using namespace std;

void swap(int * a, int *b);
int main() {
  Student s1;
  Student s2("Gavin","Kyte", 3.783);
  Student * sp;

  sp = new Student("Jill", "Coppus", 3.10);
  sp -> print();

  return 0;
}

// Deprecated for this commit
// if need access to the memory address, use pointer *
// else, use reference &
void swap(int & a, int & b) {
  int temp = a;
  a = b;
  b = temp;
}
