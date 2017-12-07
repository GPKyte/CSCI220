// Gavin Kyte
// Tue Dec  5 20:02:44 2017

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include "HashTable.cpp"
using namespace std;

// Trim methods taken from here: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

int main(){
  int collisions;
  string::size_type sz;
  HashTable<string, string> table;
  ifstream file("ted_main.csv");
  ifstream ifs;
  ifs.open("ted_main.csv", ifstream::in);
  if (file.is_open()) {
    string id;
    string headline;
    int i = 0;
    while (file >> id && getline(file, headline) && i < 504) {
      trim(headline);
      table.insert(id, headline, collisions);
      i++;
    }
    file.clear();
    file.seekg(0, file.beg);
    file.close();
  } else {
    throw(1);
  }
  cout<<table;
  cout<<collisions<<endl;
  return 0;
}
