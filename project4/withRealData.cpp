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
  string fileName = "fakeNews.txt"; // ted_main.txt (1), fakeNews.txt (2)
  ifstream file(fileName);
  ifstream ifs;
  ifs.open(fileName, ifstream::in);
  if (file.is_open()) {
    string id;
    string headline;
    int i = 0;
    while (file >> id && getline(file, headline) && i < 1009) {
      trim(headline);
      table.insert(id, headline, collisions);
      cout<<table.alpha()<<","<<collisions<<endl;
      i++;
    }
    file.clear();
    file.seekg(0, file.beg);
    file.close();
  } else {
    cout<<fileName<<" is closed. Does it exist? Do you have correct permissions?"<<endl;
    throw(1);
  }
  return 0;
}
