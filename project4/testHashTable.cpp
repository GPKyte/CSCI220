// Gavin Kyte
// Tue Dec  5 16:29:18 2017

#include <iostream>
#include <iomanip>
#include "HashTable.cpp"
using namespace std;

int main(){
  HashTable<int> table;
  int collisions = 0;
  int insertSuccesses = 0;
  int removeSuccesses = 0;
  int findSuccesses = 0;
  int num;

  for (int i=0; i<504; i++) {
    insertSuccesses += table.insert(97*i % 1009, i, collisions);
	}
  for (int i=0; i<504; i++) {
    if (i%2 == 1) removeSuccesses += table.remove(97*i % 1009);
  }
  for (int i=0; i<504; i++) {
    findSuccesses += table.find(97*i % 1009, num);
	}
  cout<<table;
  cout<<insertSuccesses<<endl<<removeSuccesses<<endl<<findSuccesses<<endl;
  return 0;
}
