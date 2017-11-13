// Gavin Kyte
// Thu Nov  2 16:06:33 2017

#include <iostream>
#include <iomanip>
#include "CourseCompare.hpp"
using namespace std;

int main(){
  CourseCompare comp;
  comp.loadCourses("inOrder.txt", "inOrder.txt");
  // comp.display();
  cout<<"Courses still needed:"<<endl;
  comp.showNeededNotTaken();
  cout<<"Courses taken but not needed:"<<endl;
  comp.showTakenNotNeeded();
  cout<<"Courses taken that are also necessary:"<<endl;
  comp.showTakenAndNeeded();
  comp.display();
  return 0;
}
