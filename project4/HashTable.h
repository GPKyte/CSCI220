#pragma once
#include "Record.h"
#define MAXHASH 1009 // Size of HashTable. Must be prime number ~twice desired amount of data

template <class K, class V> class HashTable {
private:
  Record<K, V> *hashMap; // Array of record objects
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
  bool find(K key, V& value);
  bool insert(K key, V value, int& collisions);
  float alpha();
  bool remove(K key);
  unsigned hashFunction(K key);
  unsigned probeFunction(K key, int hash);
  ~HashTable();
};
