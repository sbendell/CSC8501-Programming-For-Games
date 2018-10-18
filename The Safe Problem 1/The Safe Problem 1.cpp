// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>
#include <istream>

using namespace std;

int* RandomArray(int size, int upperbound, int lowerbound) {
	int* newArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = rand() % (upperbound + 1) + lowerbound;
	}
	return newArray;
}

int main()
{
	srand(time(NULL));
	clock_t start = clock();
	int* root = RandomArray(4, 9, 0);
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	int iterations = 10000;
	int safeSize = 5;
	int lockSize = 4;

	int validLocks = 0;
	int validLocksBonus = 0;

	for (int i = 1; i < iterations; i++)
	{
		delete[] root;
		root = RandomArray(lockSize, 9 * i, 0);
		MultiLockSafe newSafe(safeSize, lockSize, root, UHF, LHF, PHF);
		//cout << newSafe;
		//cout << "\nValid Multisafes: " << validLocks << "\n\n";
		if (newSafe.IsValid()) {
			validLocks++;
		}
		if (newSafe.IsValidBonus()) {
			validLocksBonus++;
		}
	}

	cout << "\n\n\n\nValid Multisafes: " << validLocks;
	cout << "\n\nValid Multisafes Bonus: " << validLocksBonus;
	clock_t end = clock();
	cout << "\nTime taken" << double(end - start) / CLOCKS_PER_SEC;

	int x;
	cin >> x;

	delete[] root;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

    return 0;
}

