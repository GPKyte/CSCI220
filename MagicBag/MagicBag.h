// Gavin Kyte
// Mon Sep 11 08:21:37 2017

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <exception>
using namespace std;

// Implemented with a linked list
template <class T>
class MagicBag {
private:
  struct MagicItem {
    MagicItem *next;
    T value;
  };
  int size;
  MagicItem *head;  // points to last item
public:
  MagicBag() {
    size = 0;
    head = nullptr;
  }
  MagicBag(const MagicBag& other) {
    size = other.size;
    head = nullptr;
    // Go to each item and make a copy and make links
    MagicItem *original = other.head;
    while (original) {
      MagicItem *copy = new MagicItem();
      copy -> value = original -> value;
      copy -> next = head;
      head = copy;
      original = original -> next;
    }
  }
  ~MagicBag() {
    while (head) {
      MagicItem *next = head -> next;
      delete head;
      head = next;
    }
  }
  void insert(T value) {
    MagicItem *item = new MagicItem();
    item -> value = value;
    item -> next = head;
    head = item;
    size++;
  }
  // Remove a random item from the Bag
  // "Empty" is thrown if the bag is empty
  T draw() {
    if (!size) {throw("Empty");} // Empty
    srand (time(NULL)); // set random's seed
    int randIndex = rand() % size;
    MagicItem *selection = head;
    if (randIndex == 0) { // Handle special case where head needs updated
      head = head -> next;
    } else { // Common case
      MagicItem *before = selection;
      for (int i = 1; i < randIndex; i++) {
        before = before -> next;
      }
      selection = before -> next;
      before -> next = selection -> next;
    }
    size--;
    return selection -> value;
  }
  // Counts matches
  // requires a primitive data type for comparison
  int peek(T item) {
    int count = 0;
    MagicItem *baggedItem = head;
    while (baggedItem) {
      if (baggedItem -> value == item) {count++;}
      baggedItem = baggedItem -> next;
    }
    return count;
  }
  // Print out a [] list of values in bag
  friend ostream& operator<<(ostream& os, const MagicBag& me) {
    MagicItem *item = me.head;
    cout << "[";
    if (item) { // account for empty bag
      while (item -> next) {
        cout << item -> value << ", ";
        item = item -> next;
      }
      cout << item -> value;
    }
    cout << "]";
    return os;
  }
  MagicBag& operator=(MagicBag other) {
    // Copy contents of other into this
    swap(*this, other);
    return *this;
  }
  // Learned about the Big Three from here:
  // https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
  friend void swap(MagicBag& first, MagicBag& second) {
    using std::swap;
    swap(first.size, second.size);
    swap(first.head, second.head);
  }
};
