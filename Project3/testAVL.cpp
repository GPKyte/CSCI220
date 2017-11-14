// Gavin Kyte
// Mon Nov 13 15:18:48 2017

#include <iostream>
#include <iomanip>
#include "AVLComparisonTree.hpp"
using namespace std;

int main(){
  AVLComparisonTree<int> avl;
  avl.insert(50,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(25,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(12,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(100,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(75,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(200,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(6,0);
  avl.display(avl.root, 1);
  cout<<endl<<"-----------------"<<endl;
  avl.insert(10,0);
  avl.display(avl.root, 1);
  cout<<endl;
  return 0;
}
