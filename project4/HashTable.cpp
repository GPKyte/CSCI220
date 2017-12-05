#include "HashTable.h"
#include "Record.h"
#include <string>
#include <stdio.h>

/*Generic constructor*/
template <class T> HashTable<T>::HashTable() {
  hashMap = new Record<T>[MAXHASH];
  currentSize = 0;
}

/*Finds an element with a certain key and stores it in the value passed*/
template <class T> bool HashTable<T>::find(int key, T& value) {
  int local = hashFunction(key);
  int count = 0;

  // Since MAXHASH is prime, all values 0-MAXHASH will be covered eventually
  while (count != MAXHASH) {
    if (hashMap[local].isNormal() && hashMap[local].getKey() == key) {
      value = hashMap[local].getValue();
      return true;
    } else {
      local = probeFunction(key, local);
    }
    count++;
  }
  return false;
}

/**
 * Inserts the key/value into the hashtable and
 * stores the amount of collisions in an outside memory location
 * for analysis
 */
template <class T> bool HashTable<T>::insert(int key, T value, int& collisions) {
  unsigned int local = hashFunction(key);
  int count = 0;
  while (count != MAXHASH) {
    Record<T> probe = hashMap[local];
    if (!probe.isNormal()) {
      hashMap[local] = Record<T>(key, value);
      currentSize++;
      collisions += count;
      return true;
    } else if (probe.getKey() == key) {
      hashMap[local] = Record<T>(key, value);
      return true;
    } else {
      local = probeFunction(key, local);
      count++;
    }
  }
  throw(1); // Mathematically impossible if MAXHASH is prime, practically possible via program error.
  return false;
}

/*Returns the load factor for the hash*/
template <class T> float HashTable<T>::alpha() {
  return (float)currentSize/MAXHASH;
}

/*Kills a table key*/
template <class T> bool HashTable<T>::remove(int key) {
  int local = hashFunction(key);
  int count = 0;

  // Since MAXHASH is prime, all values 0-MAXHASH will be covered eventually
  while (count != MAXHASH) {
    if (hashMap[local].isNormal() && hashMap[local].getKey() == key) {
      hashMap[local].kill();
      return true;
    } else {
      local = probeFunction(key, local);
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

#define hashsize(n) (1U << (n))
#define hashmask(n) (hashsize(n) - 1)

#define mix(a,b,c) \
{ \
    a -= b; a -= c; a ^= (c >> 13); \
    b -= c; b -= a; b ^= (a << 8); \
    c -= a; c -= b; c ^= (b >> 13); \
    a -= b; a -= c; a ^= (c >> 12); \
    b -= c; b -= a; b ^= (a << 16); \
    c -= a; c -= b; c ^= (b >> 5); \
    a -= b; a -= c; a ^= (c >> 3); \
    b -= c; b -= a; b ^= (a << 10); \
    c -= a; c -= b; c ^= (b >> 15); \
}

unsigned jen_hash(unsigned char *k, unsigned length, unsigned initval)
{
    unsigned a, b;
    unsigned c = initval;
    unsigned len = length;

    a = b = 0x9e3779b9;

    while (len >= 12)
    {
        a += (k[0] + ((unsigned)k[1] << 8) + ((unsigned)k[2] << 16) + ((unsigned)k[3] << 24));
        b += (k[4] + ((unsigned)k[5] << 8) + ((unsigned)k[6] << 16) + ((unsigned)k[7] << 24));
        c += (k[8] + ((unsigned)k[9] << 8) + ((unsigned)k[10] << 16) + ((unsigned)k[11] << 24));

        mix(a, b, c);

        k += 12;
        len -= 12;
    }

    c += length;

    switch (len)
    {
    case 11: c += ((unsigned)k[10] << 24);
    case 10: c += ((unsigned)k[9] << 16);
    case 9: c += ((unsigned)k[8] << 8);
        /* First byte of c reserved for length */
    case 8: b += ((unsigned)k[7] << 24);
    case 7: b += ((unsigned)k[6] << 16);
    case 6: b += ((unsigned)k[5] << 8);
    case 5: b += k[4];
    case 4: a += ((unsigned)k[3] << 24);
    case 3: a += ((unsigned)k[2] << 16);
    case 2: a += ((unsigned)k[1] << 8);
    case 1: a += k[0];
    }

    mix(a, b, c);

    return c;
}

unsigned simple_hash(int *key, int len) {
  return (*(key) * len + 1);
}

unsigned chooseHash(int key, int choice) {
  unsigned hash;
  if (choice == 0)
    hash = simple_hash(&key, sizeof(key));
  else if (choice == 1)
    hash = oat_hash(&key, sizeof(key));
  else if (choice == 2)
    hash = jen_hash((unsigned char*)&key, sizeof(key), 1);
  return hash % MAXHASH;
}

/*Hash function for finding the home position*/
template <class T> unsigned HashTable<T>::hashFunction(int key) {
  return chooseHash(key, 2);
}

/*Returns the offset to probe by*/
template <class T> unsigned HashTable<T>::probeFunction(int key, int hash) {
  int probe = (hash + chooseHash(key, 1)) % MAXHASH;
  if (probe == hash) probe += 5;
  return probe;
}

// template <class T> unsigned HashTable<T>::probeFunction(int key, int hash) {
//   return (hash + oat_hash(&key, sizeof(key))) % MAXHASH;
// }

/*Deallocater*/
template <class T> HashTable<T>::~HashTable() {
  delete[] hashMap;
}

//Sets what types T can be
template class HashTable<int>;
template class HashTable<float>;
template class HashTable<string>;
