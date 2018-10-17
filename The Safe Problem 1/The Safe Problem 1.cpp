// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>

using namespace std;

int* RandomArray(int size, int upperbound, int lowerbound) {
	int* newArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = rand() % (upperbound + 1 - lowerbound) + lowerbound;
	}
	return newArray;
}

int main()
{
	srand(time(NULL));
	int* root = RandomArray(4, 9, 0);
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	int UHFArray[4] = { +1, -1, +1, -1 };


	int validLocks = 0;

	for (int i = 0; i < 10000; i++)
	{
		delete[] root;
		root = RandomArray(4, 9 * i, 0);
		MultiLockSafe newSafe(5, 4, root, UHF, LHF, PHF);
		//cout << newSafe;
		//cout << "\nValid Multisafes: " << validLocks << "\n\n";
		if (newSafe.IsValid()) {
			validLocks++;
		}
	}

	cout << "\n\n\n\nValid Multisafes: " << validLocks;

	int x;
	cin >> x;

	delete[] root;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

    return 0;
}

