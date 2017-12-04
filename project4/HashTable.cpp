#include "HashTable.h"
#include "Record.h"
#include <string>

/*Generic constructor*/
template <class T> HashTable<T>::HashTable() {
  hashMap = new Record<T>[MAXHASH];
  currentSize = 0;
}

/*Finds an element with a certain key and stores it in the value passed*/
template <class T> bool HashTable<T>::find(int key, T& value) {

  return false;
}

/**
 * Inserts the key/value into the hashtable and
 * stores the amount of collisions in an outside memory location
 * for analysis
 */
template <class T> bool HashTable<T>::insert(int key, T value, int& collisions) {
  int local = hashFunction(key);
  for(;;) {
    Record<T> probe = hashMap[local];
    if (probe.isEmpty() || probe.isTombstone() || probe.getKey() == key) {
      hashMap[local] = Record<T>(key, value);
      // delete probe;
      return true;
    } else if (probe.isNormal() && probe.getKey() != key) {
      local = (local + probeFunction(key)) % MAXHASH;
    } else {
      throw(1);
    }
  }
  return false;
}

/*Returns the load factor for the hash*/
template <class T> float HashTable<T>::alpha() {
  return currentSize / MAXHASH;
}

/*Kills a table key*/
template <class T> bool HashTable<T>::remove(int key) {
  int local = hashFunction(key);
  int count = 0;

  while (count != MAXHASH) {
    if (hashMap[local].isNormal() && hashMap[local].getKey() == key) {
      hashMap[local].kill();
      return true;
    } else {
      local = (local+probeFunction(key)) % MAXHASH;
    }
    count++;
  }
  return false;
}

/*Taken and modified from http://www.eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx */
unsigned oat_hash(int *key, int len) {
    unsigned char *p = (unsigned char*)(key);
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}

/*Hash function for finding the home position*/
template <class T> int HashTable<T>::hashFunction(int key) {
  return oat_hash(&key, sizeof(key)) % MAXHASH;
}

/*The result of probing is returned with the new slot's position*/
template <class T> int HashTable<T>::probeFunction(int key) {
  return (key*key + 1) % MAXHASH;
}

/*Deallocater*/
template <class T> HashTable<T>::~HashTable() {
  delete[] hashMap;
}

//Sets what types T can be
template class HashTable<int>;
template class HashTable<float>;
template class HashTable<string>;
