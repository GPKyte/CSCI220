#include <list>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "BinarySearchTree.h"

using namespace std;
class ComparingLists
{
private:
  BinarySearchTree<string> tree;
  vector<string> list2;
  vector<string> inList2;
  vector<string> inBothLists;
public:
  string toCompare1;
  string toCompare2;
  // This is the default constructor
  // Big theta on constant
  ComparingLists()
  {
  }
  // perameter: 2 strings that are text files
  // return: void
  // This calls on methods to read in the data and compare the 2 lists
  // big theta of nlog(n)
  void startComparing(string listToCompare1, string listToCompare2)
  {
    toCompare1 = listToCompare1;
    toCompare2 = listToCompare2;
    loadData1();
    loadData2();
    compare();
  }
  // perameter: None
  // return: void
  // This loads the data from the first list into the binary search tree
  // big theta of nlog(n)
  void loadData1()
  {
    string s;
    vector<string> data;
    ifstream myfile(toCompare1);
    if (myfile.is_open())
    {
      while ( getline (myfile,s))
      {
        data.push_back(s);
      }
      myfile.close();
      while(data.size()>0)
      {
        int r1 = rand() % data.size();
        tree.insert(data[r1]);
        data.erase(data.begin() + r1);
      }
    }
    else
    {
      throw(1);
    }
  }
  // perameter: None
  // return: void
  // this loads the data from the second list into a vector
  // big theta of n
  void loadData2()
  {
    string s;
    ifstream myfile(toCompare2);
    if (myfile.is_open())
    {
      while (getline(myfile,s))
      {
        list2.push_back(s);
      }
      myfile.close();
     }
     else
     {
       throw(1);
     }
  }
  // perameter: None
  // return: void
  // This compares the two lists and then prints out the remaining elements from both lists and what both lists have in common
  // big theta of nlog(n)
  void compare()
  {

    for(int i=0; i<list2.size(); i++)
    {
      string s = tree.find(list2[i]);
      if(s != " ")
      {
        string s = list2[i];
        inBothLists.push_back(s);
      }
      else
      {
        string s = list2[i];
        inList2.push_back(s);
      }
    }
    tree.print(toCompare1);
    cout << "The elements that are only in " << toCompare2 << " are:" << endl;
    for(int i=0; i<inList2.size(); i++)
    {
      string s = inList2[i];
      cout << s << endl;
    }
    cout << endl;
    cout << "The elements in both lists are:" << endl;
    for(int i=0; i<inBothLists.size(); i++)
    {
      string s = inBothLists[i];
      cout << s << endl;
    }
    cout << endl;
  }
};
