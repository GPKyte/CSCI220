// Gavin Kyte
// Thu Nov  2 16:06:33 2017

#include <iostream>
#include <iomanip>
#include "ComparisonTree.hpp"
using namespace std;

int main(){
  ComparisonTree<int> tree;
  tree.insert(5, 0);
  tree.insert(2, 0);
  tree.insert(9, 1);
  tree.insert(7, 1);
  tree.display(tree.root, 1);
  cout<<endl;
  return 0;
}
