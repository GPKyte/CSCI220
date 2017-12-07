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
 * @param V value, A value, no (known) restrictions beyond type or reasonable size
 * @param int& collisions, Reference to outside variable to track collision count
 */
template <class K, class V> bool HashTable<K, V>::insert(K key, V value, int& collisions) {
  unsigned int local = hashFunction(key);
  int count = 0;
  while (count != MAXHASH) {
    // Note: sometimes probe will come back as not normal, tombstone, or empty. Bug?
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
  }
  std::cout<<local<<std::endl;
  throw(1); // Mathematically impossible, practically possible via program error.
  return false;
}

/*Returns the load factor for the hash*/
template <class K, class V> float HashTable<K, V>::alpha() {
  return (float)currentSize/MAXHASH; // Casting to get float division instead of int div
}

/*Kills a table key*/
template <class K, class V> bool HashTable<K, V>::remove(K key) {
  int local = hashFunction(key);
  int count = 0;

  // Since MAXHASH is prime, all values 0-MAXHASH will be covered eventually
  while (count != MAXHASH) {
    if (hashMap[local].isNormal() && hashMap[local].getKey() == key) {
      hashMap[local].kill();
      currentSize--;
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
 * @param unsigned char* key, A pointer to a key, interpreted on byte level
 * @param int len, Length of the key in bytes. Use sizeof(key)
 * @return unsigned int, A positive int serving as hash code for key
 */
unsigned oat_hash(unsigned char *key, int len) {
  unsigned h = 0;

  for (int i = 0; i < len; i++) {
    h += key[i];
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
 * @param unsigned char *k, Reference to a (probably casted) variable for a unique ID
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
 * @param size_t key, The hashed size value of a unique identifier for hash table
 * @param int choice, The hash function to use
 * @return a positive int < MAXHASH to serve as hash code
 */
unsigned chooseHash(size_t key, int choice) {
  unsigned hash;
  if (choice == 0)
    hash = key % MAXHASH;
  else if (choice == 1)
    hash = oat_hash((unsigned char*)&key, sizeof(key));
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
  size_t keyVal = std::hash<K>{}(key);
  return chooseHash(keyVal, 2);
}

/**
 * Increment the home hash by probe amount
 * @param K key, A unique identifier for dictionary
 * @param int hash, The hash table index that resulted in a collision
 * @return a positive int < MAXHASH to serve as next array index
 */
template <class K, class V> unsigned HashTable<K, V>::probeFunction(K key, int hash) {
  size_t keyVal = std::hash<K>{}(key);
  unsigned int probe = hash + chooseHash(keyVal, 1);
  if (probe % MAXHASH == hash) probe += 5;
  return probe % MAXHASH;
}

/*Deallocater*/
template <class K, class V> HashTable<K, V>::~HashTable() {
  delete[] hashMap;
}

//Sets what types K and V can be
template class HashTable<int, int>;
template class HashTable<int, float>;
template class HashTable<int, string>;
template class HashTable<float, int>;
template class HashTable<float, float>;
template class HashTable<float, string>;
template class HashTable<string, int>;
template class HashTable<string, float>;
template class HashTable<string, string>;
