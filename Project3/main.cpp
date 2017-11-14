// Gavin Kyte
// Thu Nov  2 16:06:33 2017

#include <iostream>
#include <iomanip>
#include "AVLComparisonTree.hpp"
using namespace std;

int main(){
  AVLComparisonTree<string> comp;
  comp.loadData("coursesNeeded.txt", "coursesTaken.txt");
  comp.compareLists();
  comp.display();
  return 0;
}
