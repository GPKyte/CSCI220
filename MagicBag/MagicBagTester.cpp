// Gavin Kyte
// Mon Sep 11 08:45:00 2017

#include <iostream>
#include <iomanip>
#include "MagicBag.h"
using namespace std;

int main(){
  MagicBag<int> interestingBag;
  MagicBag<float> floatingBag;
  MagicBag<double> bDubsBag;
  MagicBag<char> charredBag;
  MagicBag<bool> enlightenedBag;
  int numbers[] = {1,2,9,0,8,5,87,45,3,56,7,99,1,87,87,87,2,23};
  float floaters[] = {1.2,9.009,8.5,8.7,45.3,56.7,9.91,87.87,8.7,2.23};
  double bdubs[] = {1.2,9.009,8.5,8.7,1.2,1.2,1.2,1.2,1.2,1.2,8.7,2.23};
  char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  bool truth[] = {true,false,true,false,false,false,true,false,false,true,true};

  for (int n : numbers) {interestingBag.insert(n);}
  for (float f : floaters) {floatingBag.insert(f);}
  for (double d : bdubs) {bDubsBag.insert(d);}
  for (char c : alphabet) {charredBag.insert(c);}
  for (bool b : truth) {enlightenedBag.insert(b);}

  cout << "operator <<:" << endl;
  cout << "   int:    " << interestingBag << endl;
  cout << "   float:  " << floatingBag << endl;
  cout << "   double: " << bDubsBag << endl;
  cout << "   char:   " << charredBag << endl;
  cout << "   bool:   " << enlightenedBag << endl;
  cout << endl;

  cout << "int peek(T item):" << endl;
  cout << "   Peeked for int 9 and found it " << interestingBag.peek(9) << " times" << endl;
  cout << "   Peeked for float 8.7987 and found it " << floatingBag.peek(8.7987) << " times" << endl;
  cout << "   Peeked for double 1.2 and found it " << bDubsBag.peek(1.2) << " times" << endl;
  cout << "   Peeked for char 'c' and found it " << charredBag.peek('c') << " times" << endl;
  cout << "   Peeked for bool true and found it " << enlightenedBag.peek(true) << " times" << endl;
  cout << endl;

  cout << "T draw():" << endl;
  cout << "   Drew a " << interestingBag.draw() << " randomly from int bag." << endl;
  cout << "   Drew a " << floatingBag.draw() << " randomly from float bag." << endl;
  cout << "   Drew a " << bDubsBag.draw() << " randomly from double bag." << endl;
  cout << "   Drew a " << charredBag.draw() << " randomly from char bag." << endl;
  cout << "   Drew a " << enlightenedBag.draw() << " randomly from bool bag." << endl;
  cout << endl;

  return 0;
}
