#pragma once
#include "Record.h"
#define MAXHASH 1009 // Size of HashTable. Must be prime number ~twice desired amount of data

template <class T> class HashTable {
private:
  Record<T> *hashMap; // Array of record objects
  int currentSize; // Number of key/value pairs stored in hashMap array

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
  unsigned probeFunction(int key, int hash);
  ~HashTable();
};
