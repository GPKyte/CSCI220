// Gavin Kyte
// Mon Nov 13 15:18:48 2017

#include <iostream>
#include <iomanip>
#include "AVLComparisonTree.hpp"
using namespace std;

int main(){
  AVLComparisonTree<int> avl;
  avl.insert(1,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(2,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(3,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(4,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(5,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(6,0);
  avl.display(avl.root, 1);
  cout<<endl;
  return 0;
}
