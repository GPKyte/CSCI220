#pragma once
#include "Record.h"
#define MAXHASH 1009

template <class T> class HashTable {
private:
  Record<T> *hashMap;
  int currentSize;
  //friend function for << operator.
  friend ostream& operator<<(ostream& os, const HashTable& me) {
    for (int i = 0; i < MAXHASH; i++) {
      cout<<me.hashMap[i]<<endl;
    }
    return os;
  }

public:
  HashTable();
  bool find(int key, T& value);
  bool insert(int key, T value, int& collisions);
  float alpha();
  bool remove(int key);
  unsigned hashFunction(int key);
  unsigned probeFunction(int key);
  unsigned probeFunction(int key, int count);
  ~HashTable();
};
