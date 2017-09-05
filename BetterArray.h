#include <iostream>
using namespace std;

class BetterArray{
private:
  int * buffer;
  int size;
public:
  BetterArray(){
    size = 0;
    buffer = NULL;
  }
  BetterArray(int newSize){
    size = newSize;
    buffer = new int[size];
  }
  ~BetterArray(){
    if (buffer) //Can write this in one line, style preference
      delete(buffer);
  }
  //BetterArray(int size){
  //  this -> size = size;
  //}

  int& operator[](int index){
    if(size <= index || index < 0){
      throw(1);
    }
    return buffer[index];
  }
  // Since ostream is another class, we use "friend"
  friend ostream& operator<<(ostream& os, const BetterArray& me){
    os << "[";
    for (int i = 0; i < me.size -1; i++){
      os << me.buffer[i] << ", ";
    }
    os << me.buffer[me.size - 1] << "]";
    return os;
  }
};
