#include "HashTable.h"
#include "Record.h"
#include <string>

/*Generic constructor*/
template <class T> HashTable<T>::HashTable()
{
    hashMap = new Record<T>[MAXHASH];
    currentSize = 0;
}

/*Finds an element with a certain key and stores it in the value passed*/
template <class T> bool HashTable<T>::find(int key, T& value) {

    return false;

}

/*Inserts the key/value into the hashtable and stores the amount of collisions in the passed collisions*/
template <class T> bool HashTable<T>::insert(int key, T value, int& collisions) {

    return false;
}

/*Returns the load factor for the hash*/
template <class T> float HashTable<T>::alpha() {
    return currentSize / 1000.00;
}

/*Kills a table key*/
template <class T> bool HashTable<T>::remove(int key)
{
    int local = hashFunction(key);
    int count = 0;

    while (count != MAXHASH) {
        if (hashMap[local].isNormal() && hashMap[local].getKey() == key) {
            hashMap[local].kill();
            return true;
        }
        else {
            local = probeFunction(local);
        }
        count++;
    }
    return false;
}

/*Hash function for finding the home position*/
template <class T> int HashTable<T>::hashFunction(int key) {
    return 0;
}

/*The result of probing is returned with the new slot's position*/
template <class T> int HashTable<T>::probeFunction(int key) {
    return 0;
}

/*Deallocater*/
template <class T> HashTable<T>::~HashTable()
{
    delete[] hashMap;
}

//Sets what types T can be
template class HashTable<int>;
template class HashTable<float>;
template class HashTable<string>;
