// Gavin Kyte
// Mon Sep 11 08:21:37 2017

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <exception>
using namespace std;

template <class T>
class MagicBag {
private:
  struct MagicItem {
    MagicItem *next;
    T value;
  };
  int size;
  MagicItem *head;  // -> '' of last item
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
  T draw() {
    if (!size) {throw("Empty");} // Empty
    srand (time(NULL)); // set random's seed
    int randIndex = rand() % size;
    MagicItem *selection = head;
    if (randIndex == 0) {
      head = head -> next;
    } else {
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
  int peek(T item) {
    int count = 0;
    MagicItem *baggedItem = head;
    while (baggedItem) {
      if (baggedItem -> value == item) {count++;}
      baggedItem = baggedItem -> next;
    }
    return count;
  }
  friend ostream& operator<<(ostream& os, const MagicBag& me) {
    MagicItem *item = me.head;
    cout << "[";
    if (item) {
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
    // Copy contents of other into this bag
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
