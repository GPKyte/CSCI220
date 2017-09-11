// Gavin Kyte
// Mon Sep 11 08:21:37 2017

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <exception>
using namespace std;

class MagicBag {
private:
  struct MagicItem {
    MagicItem *next;
    int value;
  };
  int size;
  MagicItem * start; // -> MemRef of first item
  MagicItem * end;   // -> '' of last item
public:
  MagicBag() {
    size = 0;
    start = nullptr;
    end = nullptr;
  }
  MagicBag(const MagicBag& other) {}
  ~MagicBag(){}

  void insert(int value) {
    //cout << "end value is " << end -> getValue() << endl;
    MagicItem *item = new MagicItem();
    item -> value = value;
    if (size == 0) {start = item;}
    if (end) {end -> next = item;}
    end = item;
    size++;
  }
  void print() {
    MagicItem *item = start;
    cout << "[";
    for (int i = 0; i+1 < size; i++) {
      cout << item -> value << ", ";
      item = item -> next;
    }
    cout << item -> value << "]" << endl;
  }
  int draw() {
    //srand ( time(NULL) ); // set random's seed
    MagicItem * previous = nullptr;
    MagicItem * item = start;

    //int randIndex = rand() % size;
    int randIndex = 0;
    cout << "In bag. Draw #" << randIndex << endl;
    if (randIndex == 0) {
      start = start -> next;
      return item -> value;
    }

    // Note that we start i at 1 because we start before the loop
    // also we add one to stop early and link to surrounding items in list
    for (int i = 1; i < randIndex; i++) {
      item = item -> next;
    }
    previous = item;
    item = item -> next;
    previous -> next = item -> next;
    return item -> value;
  }
  int peek(int item) {
    // Put exception here?
    if (size == 0) {cout << "No items to peek at" << endl;}
    int count = 0;
    MagicItem *baggedItem = start;
    for (int i = 0; i < size; i++) {
      if (baggedItem -> value == item) {count++;}
      baggedItem = baggedItem -> next;
    }
    return count;
  }
};
