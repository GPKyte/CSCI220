// Gavin Kyte
// Mon Sep 11 08:45:00 2017

#include <iostream>
#include <iomanip>
#include <string>
#include "MagicBag.h"
using namespace std;

int main(){
  // Shallow example to show that bag can hold as much as memory allows
  // MagicBag<int> infiniteBag;
  // int i = 0;
  // while (i < 999999) {
  //   infiniteBag.insert(9);
  //   i++;
  // }
  // cout << infiniteBag << endl;
  // return 0;

  MagicBag<int> interestingBag;
  MagicBag<float> floatingBag;
  MagicBag<double> bDubsBag;
  MagicBag<char> charredBag;
  MagicBag<bool> enlightenedBag;
  MagicBag<string> bookBag;
  int numbers[] = {1,2,9,0,8,5,87,45,3,56,7,99,1,87,87,87,2,23};
  float floaters[] = {1.2,9.009,8.5,8.7,45.3,56.7,9.91,87.87,8.7,2.23};
  double bdubs[] = {1.2,9.009,8.5,8.7,1.2,1.2,1.2,1.2,1.2,1.2,8.7,2.23};
  char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  bool truth[] = {true,false,true,false,false,false,true,false,false,true,true};
  string dictionary[] = {"Hello","this","is","world"};

  for (int i=0; i < sizeof(numbers)/sizeof(numbers[0]); i++)
    {interestingBag.insert(numbers[i]);}
  for (int i=0; i < sizeof(floaters)/sizeof(floaters[0]); i++)
    {floatingBag.insert(floaters[i]);}
  for (int i=0; i < sizeof(bdubs)/sizeof(bdubs[0]); i++)
    {bDubsBag.insert(bdubs[i]);}
  for (int i=0; i < sizeof(alphabet)/sizeof(alphabet[0]); i++)
    {charredBag.insert(alphabet[i]);}
  for (int i=0; i < sizeof(truth)/sizeof(truth[0]); i++)
    {enlightenedBag.insert(truth[i]);}
  for (int i=0; i < sizeof(dictionary)/sizeof(dictionary[0]); i++)
    {bookBag.insert(dictionary[i]);}

  cout << "operator <<:" << endl;
  cout << "   int:    " << interestingBag << endl;
  cout << "   float:  " << floatingBag << endl;
  cout << "   double: " << bDubsBag << endl;
  cout << "   char:   " << charredBag << endl;
  cout << "   bool:   " << enlightenedBag << endl;
  cout << "   string: " << bookBag << endl;
  cout << endl;

  cout << "int peek(T item):" << endl;
  cout << "   Peeked for int 9 and found it " << interestingBag.peek(9) << " times" << endl;
  cout << "   Peeked for float 8.7987 and found it " << floatingBag.peek(8.7987) << " times" << endl;
  cout << "   Peeked for double 1.2 and found it " << bDubsBag.peek(1.2) << " times" << endl;
  cout << "   Peeked for char 'c' and found it " << charredBag.peek('c') << " times" << endl;
  cout << "   Peeked for bool true and found it " << enlightenedBag.peek(true) << " times" << endl;
  cout << "   Peeked for string 'Hello' and found it " << bookBag.peek("Hello") << " times" << endl;
  cout << endl;

  cout << "T draw():" << endl;
  cout << "   Drew a " << interestingBag.draw() << " randomly from int bag." << endl;
  cout << "   Drew a " << floatingBag.draw() << " randomly from float bag." << endl;
  cout << "   Drew a " << bDubsBag.draw() << " randomly from double bag." << endl;
  cout << "   Drew a " << charredBag.draw() << " randomly from char bag." << endl;
  cout << "   Drew a " << enlightenedBag.draw() << " randomly from bool bag." << endl;
  cout << "   Drew a " << bookBag.draw() << " randomly from string bag." << endl;
  cout << endl;

  cout << "operator =:" << endl;
  MagicBag<int> a;
  cout << "   Bag a before assignment: " << a << endl;
  a = interestingBag;
  cout << "   Bag a after assignment:  " << a << endl;
  cout << endl;

  cout << "Bags in bags:" << endl;
  MagicBag<MagicBag<bool> > superbag;
  superbag.insert(enlightenedBag);
  superbag.insert(enlightenedBag);
  cout << "   Bagception: " << superbag << endl;
  // cout << "Peeking " << superbag.peek(superbag) << endl; // Can't do binary comparison and .equals() DNE
  cout << "   Draw bag: " << superbag.draw() << endl;
  cout << "   Draw bag's bag's item: " << (superbag.draw()).draw() << endl;
  cout << endl;

  cout << "Edge cases:" << endl;
  MagicBag<int> edgeBag;
  edgeBag.insert(5);
  cout << "   Peek with only one item: " << edgeBag.peek(5) << endl;
  cout << "   Peek with diff data type: " << edgeBag.peek('5') << endl;
  cout << "   Draw with only one item: " << edgeBag.draw() << endl;
  cout << "   Peek with no items: " << edgeBag.peek(5) << endl;
  cout << "   The next line will be an intentially thrown error" << endl << "[Press ENTER]";
  cin.get();
  cout << "   Draw on empty bag: " << endl;
  try {
    cout << "   " << edgeBag.draw() << endl;
  } catch (char const* code) {
    cout << "Could not draw from bag. Reason: " << code << endl;
    cout << "End Main" << endl;
    return 1;
  }
  return 0;
}
