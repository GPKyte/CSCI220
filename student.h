

#include <iostream>
#include <string>

using namespace std;

class Student {
private:
  string firstName;
  string lastName;
  float gpa;
  int * grades;

public:
  Student(){
    firstName = "Invalid";
    lastName = "Invalid";
    gpa = -1.0;
    grades = new int[25];
  }

  Student(string newFirst, string newLast, float newGpa){
    firstName = newFirst;
    lastName = newLast;
    gpa = newGpa;
    grades = new int[25];
  }

  // Deconstructor
  ~Student(){
    // Prevent Memory Leaks
    delete(grades);
    cout << "Cleanup on " << this << endl;
  }

  void print(){
    cout << firstName << " " << lastName << " " << gpa << endl;
  }


};
