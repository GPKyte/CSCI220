// Gavin Kyte
// Thu Sep 14 14:12:51 2017

#include <iostream>
#include <iomanip>
using namespace std;

class betterArray{
private:
  int *buffer;
  unsigned int size;

public:

  betterArray(int newSize) {
    size = newSize;
    buffer = new int[size];
  }

  int operator[](unsigned int index) {
    if (index < size)
      return(buffer[index]);
    else
      throw(1);
  }
};

int main(){
  betterArray a(3);
  // This generates an error because [] op returns an int value
  // instead of an assignable memory address,
  // i.e. '5 = 9' is wrong but var a of value 5 can do 'a = 9'
  // We can fix this by returning a mem address from the [] overflow
  a[2] = 5;
  return 0;
}
