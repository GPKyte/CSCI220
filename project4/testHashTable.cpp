// Gavin Kyte
// Tue Dec  5 16:29:18 2017

#include <iostream>
#include <iomanip>
#include "HashTable.cpp"
using namespace std;

int main(){
  HashTable<string, string> stringyTable;
  int stringyCollisions = 0;
  for (float i=0; i<1009; i++) {
    stringyTable.insert("Key "+to_string(i), to_string(rand()), stringyCollisions);
  }
  cout<<"String table:"<<endl;
  cout<<stringyTable.alpha()<<","<<stringyCollisions<<endl;

  HashTable<float, float> floatingTable;
  int floatingCollisions = 0;
  for (float i=0.111111; i<1009; i++) {
    floatingTable.insert(i, (float)rand()/i, floatingCollisions);
  }
  cout<<"Float table:"<<endl;
  cout<<floatingTable.alpha()<<","<<floatingCollisions<<endl;

  HashTable<int, int> table;
  int collisions = 0;
  int insertSuccesses = 0;
  int removeSuccesses = 0;
  int findSuccesses = 0;
  int num;

  for (int i=0; i<504; i++) {
    insertSuccesses += table.insert(97*i, i, collisions);
	}
  for (int i=0; i<504; i++) {
    if (i%2 == 0) removeSuccesses += table.remove(97*i);
  }
  for (int i=0; i<504; i++) {
    findSuccesses += table.find(97*i, num);
	}
  cout<<"Int table:"<<endl;
  cout<<table;
  cout<<"Inserted: "<<insertSuccesses<<endl;
  cout<<"Removed: "<<removeSuccesses<<endl;
  cout<<"Found remaining: "<<findSuccesses<<endl;
  return 0;
}
