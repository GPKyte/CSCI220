
#include "HashTable.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
	/* initialize random seed: */
	srand((unsigned int)time(0));
	int collisions = 0;
	HashTable<int, int> table;
	for (int i=0; i<504; i++) {
		table.insert(rand(), rand(), collisions);
	}
	// cout<<table;
	cout << collisions << endl;
	return 0;
}
