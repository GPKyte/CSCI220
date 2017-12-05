#include "ComparingLists.cpp"
#include <string>
// perameter: none // mispelled parameter
// return: int
// this is the main of the program and runs everything
// big theta of nlog(n)
int main()
{
  ComparingLists c;
  string list1;
  string list2;
  cout << "Type name of first file being compared:" << endl;
  getline (cin, list1);
  cout << "Type name of second file being compared:" << endl;
  getline (cin, list2);
  c.startComparing(list1, list2);
  return 0;
}
