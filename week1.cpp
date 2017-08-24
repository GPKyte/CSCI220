//Week 1A
// Gavin Kyte
#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {

  int arr1[10][10];
  for (int i = 0; i < 10; i++){
    for (int j = 1; j <= 10; j++){
      int num = i*10 + j;
      arr1[i][j] = num;
      cout << setw(6) << num;
    }
    cout << endl;
  }
  char str[256];
  cout << "Enter Anything: ";
  cin >> str;

  // How to handle spaces
  cin.getline(str, 256);
  cout << str << endl;

  // Methods for handling input errors
  if (cin.fail()){
    cin.clear();
    cin.ignore();
  }
  return 0;
}
