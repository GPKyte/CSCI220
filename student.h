

#include <iostream>
#include <string>

using namespace std;

class Student {
private:
  string firstName;
  string lastName;
  float gpa;
//protected: inheritance

public:
  Student(){
    firstName = "Invalid";
    lastName = "Invalid";
    gpa = -1.0;

  }

  Student(string newFirst, string newLast, float newGpa){
    firstName = newFirst;
    lastName = newLast;
    gpa = newGpa;
  }

  ~Student(){

  }
  void print(){
    cout << firstName << " " << lastName << " " << gpa << endl;
  }


};
