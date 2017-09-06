// Gavin Kyte
// Cpp copy of java ArrayExamples

#include <vector>
#include <iterator>
#include <iostream>
#include <iomanip>
using namespace std;
int findMin(vector<int>);
// void badResize(int, int);
// int goodResize(int, int);
// void findAndPrintPairs(int, int);
// void bubblesort(int);
// void showList(int);
// int isAscending(int);
int main(){
  int arr[] = {1, 2, 3, 4, 0, 2, 3};

  vector<int> list(arr, arr + sizeof(arr)/sizeof(arr[0]));
  cout << findMin(list) << endl;
  // findAndPrintPairs(list, 5);
  // bubblesort(list);
  // showList(list);

  // list = new { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  // bubblesort(list);
  // showList(list);
  //
  // list = new int[]{11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2};
  // bubblesort(list);
  // showList(list);
  //
  // list = new int[]{1};
  // bubblesort(list);
  // showList(list);
  return 0;
}
int findMin(vector<int> list) {
  if (list.size() <= 0)
    return -1;
  int indexOfMin = 0;
  for (int i = 0; i < list.size(); i++) {
    if (list[i] < list[indexOfMin]) {
      indexOfMin = i;
    }
  }
  return indexOfMin;
}
