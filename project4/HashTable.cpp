#include "HashTable.h"
#include "Record.h"
#include <string>
#include <stdio.h>

/*Generic constructor*/
template <class K, class V> HashTable<K, V>::HashTable() {
  hashMap = new Record<K, V>[MAXHASH];
  currentSize = 0;
}

/*Finds an element with a certain key and stores it in the value passed*/
template <class K, class V> bool HashTable<K, V>::find(K key, V& value) {
  int local = hashFunction(key);
  int count = 0;

  // Since MAXHASH is prime, all values 0-MAXHASH will be covered worstcase
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
 * Inserts the key/value into the hashtable and stores the amount
 * of collisions in an outside memory location for analysis
 * @param K key, A unique identifier
 * @param V value, A value of the accepted type T, no restrictions beyond type
 * @param int& collisions, Reference to outside variable to track collision history
 */
template <class K, class V> bool HashTable<K, V>::insert(K key, V value, int& collisions) {
  unsigned int local = hashFunction(key);
  int count = 0;
  while (count != MAXHASH) {
    Record<K, V> probe = hashMap[local];
    if (!probe.isNormal()) {
      hashMap[local] = Record<K, V>(key, value);
      currentSize++;
      collisions += count;
      return true;
    } else if (probe.getKey() == key) {
      hashMap[local] = Record<K, V>(key, value);
      return true;
    } else {
      local = probeFunction(key, local);
      count++;
    }
    if (count > MAXHASH/2) std::cout << local << std::endl;
  }
  std::cout<<local<<std::endl;
  throw(1); // Mathematically impossible if MAXHASH is prime, practically possible via program error.
  return false;
}

/*Returns the load factor for the hash*/
template <class K, class V> float HashTable<K, V>::alpha() {
  return (float)currentSize/MAXHASH;
}

/*Kills a table key*/
template <class K, class V> bool HashTable<K, V>::remove(K key) {
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

/**
 * Taken and modified from http://www.eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
 * @param K* key, A pointer to a key
 * @param int len, Length of the key in bytes. Use sizeof(key)
 * @return unsigned int, A positive int serving as hash code for key
 */
template <class K> unsigned oat_hash(K *key, int len) {
    unsigned char *p = (unsigned char*)(key);
    unsigned h = 0;

    for (int i = 0; i < len; i++) {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}

// Definitions for the Jenkins Hash
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

/**
 * The Jenkins hash as seen here:
 *   http://www.eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx
 * It's an overly complex hash at bit level; it does a good job.
 * @param unsigned char *k, Reference to a probably (casted) variable for a unique ID
 * @param unsigned length, The length of k, it works to say sizeof(k)
 * @param unsigned initval, Any desired value to mix against k
 * @return unsigned int, A positive int serving as hash code for k
 */
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

/**
 * Unnecessary but helpful abstraction to allow easy change of hash in test phase
 * @param K key, A unique identifier for dictionary
 * @param int choice, The hash function to use
 * @return a positive int < MAXHASH to serve as hash code
 */
template <class K> unsigned chooseHash(K key, int choice) {
  unsigned hash;
  if (choice == 1)
    hash = oat_hash(&key, sizeof(key));
  else if (choice == 2)
    hash = jen_hash((unsigned char*)&key, sizeof(key), 1);
  return hash % MAXHASH;
}

/**
 * Hash function for finding the home position
 * @param K key, A unique identifier for dictionary
 * @return a positive int < MAXHASH to serve as array index
 */
template <class K, class V> unsigned HashTable<K, V>::hashFunction(K key) {

  return chooseHash(key, 2);
}

/**
 * Increment the home hash by probe amount
 * @param K key, A unique identifier for dictionary
 * @param int hash, The hash table index that resulted in a collision
 * @return a positive int < MAXHASH to serve as next array index
 */
template <class K, class V> unsigned HashTable<K, V>::probeFunction(K key, int hash) {
  int probe = (hash + chooseHash(key, 1)/MAXHASH) % MAXHASH;
  if (probe == hash) probe += 5;
  return probe;
}

/*Deallocater*/
template <class K, class V> HashTable<K, V>::~HashTable() {
  delete[] hashMap;
}

//Sets what types K, V can be
template class HashTable<int, int>;
template class HashTable<int, float>;
template class HashTable<int, string>;
template class HashTable<string, int>;
template class HashTable<string, float>;
template class HashTable<string, string>;
