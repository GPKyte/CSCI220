
#include "HashTable.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
	/* initialize random seed: */
	srand((unsigned int)time(0));
	int collisions = 0;
	HashTable<int> table;
	for (int i=0; i<100; i++) {
		table.insert(i, rand(), collisions);
	}
	cout << table << endl;
	return 0;
}
