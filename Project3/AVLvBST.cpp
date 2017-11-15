// Gavin Kyte
// Tue Nov 14 18:55:33 2017

#include <iostream>
#include <iomanip>
#include <chrono>
#include "AVLComparisonTree.hpp"
#include "ComparisonTree.hpp"
using namespace std;

int main(){
  AVLComparisonTree<string> warmup;
  warmup.loadData("coursesNeeded.txt", "coursesNeeded.txt");
  ComparisonTree<string> normwarmup;
  normwarmup.loadData("coursesNeeded.txt", "coursesNeeded.txt");

  long long avlLoad, avlComp, normLoad, normComp;
  int i = 0;
  while(i < 20) {
    AVLComparisonTree<string> avl;
    ComparisonTree<string> norm;
    auto t1 = chrono::high_resolution_clock::now();
    norm.loadData("coursesTaken.txt", "coursesNeeded.txt");
    auto t2 = chrono::high_resolution_clock::now();
    norm.compareLists();
    auto t3 = chrono::high_resolution_clock::now();
    avl.loadData("coursesTaken.txt", "coursesNeeded.txt");
    auto t4 = chrono::high_resolution_clock::now();
    avl.compareLists();
    auto t5 = chrono::high_resolution_clock::now();

    avlLoad += chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    avlComp += chrono::duration_cast<chrono::milliseconds>(t3-t2).count();
    normLoad += chrono::duration_cast<chrono::milliseconds>(t4-t3).count();
    normComp += chrono::duration_cast<chrono::milliseconds>(t5-t4).count();
    i++;
  }
  avlLoad /= 100;
  avlComp /= 100;
  normLoad /= 100;
  normComp /= 100;
  cout<<avlLoad<<endl<<avlComp<<endl<<normLoad<<endl<<normComp<<endl;
  return 0;
}
