// Week 2A
// Gavin Kyte

#include <iostream>
#include <iomanip>
using namespace std;

// returnType, MethodName(paramType, [paramType,...]);
// template, <class T> T MethodName(T, [T,...]);    T == var for "type"
template <class T> T getValueInRange(T, T);

int main() {
  int a = 6; int b = 25;
  float c = 1.0987; float d = 102.938;
  int res1 = getValueInRange(a, b);
  float res2 = getValueInRange(c, d);
  cout << res1 << endl;
  cout << res2 << endl;
  return 0;
}

template <class T> T getValueInRange(T low, T high){
  while (1) {
    cout << "Enter a value between " << low << " and " << high << ": " ;
    cout.flush();
    // Good practice to initialize values that aren't immediately overwritten.
    //    Bc cpp grabs open memory that could have any value.
    T value;
    // Not error checking
    cin >> value;
    if (value >= low && value <= high){
      return value;
    } else {
      cout << "Invalid" << endl;
    }
  }
}
