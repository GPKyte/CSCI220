// Gavin Kyte
// Thu Nov  2 16:09:41 2017

#include <iostream>
#include <iomanip>
#include <fstream>
#include "ComparisonTree.hpp"
using namespace std;

enum itemType {TAKEN, NEEDED};

class CourseCompare {
private:
  ComparisonTree<string> tree;

public:
  CourseCompare() {
    ComparisonTree<string> tree;
  }
  void loadCourses(string file1, string file2) {
    ifstream myFirstFile(file1);
    ifstream mySecondFile(file2);
    if(myFirstFile.is_open() && mySecondFile.is_open()) {
      string course;
      while(getline(myFirstFile, course)) {
        tree.insert(course, TAKEN);
      }
      myFirstFile.clear();
      myFirstFile.seekg(0, myFirstFile.beg);
      myFirstFile.close();
      while(getline(mySecondFile, course)) {
        tree.insert(course, NEEDED);
      }
      mySecondFile.clear();
      mySecondFile.seekg(0, mySecondFile.beg);
      mySecondFile.close();
    }else
    throw(1);
  }

  void display() {
    tree.display(tree.root, 1);
    cout<<endl;
  }
  void showNeededNotTaken() {
    tree.showBNotA(tree.root);
  }
  void showTakenNotNeeded() {
    tree.showANotB(tree.root);
  }
  void showTakenAndNeeded() {
    tree.showAAndB(tree.root);
  }

};
