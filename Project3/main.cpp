// Gavin Kyte
// Thu Nov  2 16:06:33 2017

#include <iostream>
#include <iomanip>
#include "CourseCompare.hpp"
using namespace std;

int main(){
  CourseCompare comp;
  comp.loadCourses("coursesTaken.txt", "coursesNeeded.txt");
  comp.display();
  return 0;
}
