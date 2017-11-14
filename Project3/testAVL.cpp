// Gavin Kyte
// Mon Nov 13 15:18:48 2017

#include <iostream>
#include <iomanip>
#include "AVLComparisonTree.hpp"
using namespace std;

int main(){
  AVLComparisonTree<int> avl;
  avl.insert(50,0);
  avl.display();
  cout<<endl<<"-----------------"<<endl;
  avl.insert(25,0);
  avl.display();
  cout<<endl<<"----------------- LL Rotation:"<<endl;
  avl.insert(12,0);
  avl.display();
  cout<<endl<<"----------------- No Rotation:"<<endl;
  avl.insert(100,0);
  avl.display();
  cout<<endl<<"----------------- RL Rotation:"<<endl;
  avl.insert(75,0);
  avl.display();
  cout<<endl<<"----------------- RR Rotation:"<<endl;
  avl.insert(200,0);
  avl.display();
  cout<<endl<<"-----------------"<<endl;
  avl.insert(6,0);
  avl.display();
  cout<<endl<<"----------------- LR Rotation:"<<endl;
  avl.insert(10,0);
  avl.display();
  cout<<endl;

  AVLComparisonTree<string> blankTree;
  cout<<"Test loading blank file"<<endl;
  blankTree.loadData("blank.txt", "blank.txt");
  blankTree.compareLists();
  return 0;
}
