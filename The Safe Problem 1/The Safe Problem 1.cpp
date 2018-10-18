// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int* RandomArray(int size, int upperbound, int lowerbound) {
	int* newArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = rand() % (upperbound + 1) + lowerbound;
	}
	return newArray;
}

int ArrayToInt(int size, int* arr) {
	int value = 0;

	for (int i = 0; i < size; i++)
	{
		value += (arr[i] * (int)pow(10, size - 1 - i));
	}
	return value;
}

void OutputHash(int* hash, int size, ofstream& stream) {
	for (int i = 0; i < size; i++)
	{
		if (i == 0) {
			stream << "UHF " << hash[i];
		}
		else {
			stream << "," << hash[i];
		}
	}
	stream << endl;
}

int main()
{
	srand(time(NULL));
	clock_t start = clock();
	int* root = RandomArray(4, 9, 0);
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	int iterations = 1000000;
	int safeSize = 5;
	int lockSize = 4;

	vector<int> roots;
	roots.reserve(iterations / 20);
	int validLocks = 0;
	int validLocksBonus = 0;
	string filename = "key.txt";
	ofstream datafile;

	try {
		for (int i = 1; i < iterations; i++)
		{
			MultiLockSafe newSafe(safeSize, lockSize, root, UHF, LHF, PHF);
			//cout << newSafe;
			//cout << "\nValid Multisafes: " << validLocks << "\n\n";
			if (newSafe.IsValid()) {
				validLocks++;
				roots.push_back(ArrayToInt(lockSize, root));
			}
			if (newSafe.IsValidBonus()) {
				validLocksBonus++;
			}

			delete[] root;
			root = RandomArray(lockSize, 9 * i, 0);
		}

		datafile.open(filename.c_str());

		if (datafile.fail())
			throw invalid_argument("no file exists " + filename);

		datafile << "NS " << validLocks << endl;
		for (int i = 0; i < roots.size(); i++)
		{
			datafile << roots[i] << endl;
			OutputHash(UHF, lockSize, datafile);
			OutputHash(LHF, lockSize, datafile);
			OutputHash(PHF, lockSize, datafile);
		}
	}
	catch(invalid_argument& iae) {
		cout << iae.what();
	}

	cout << "\n\n\n\nValid Multisafes: " << validLocks;
	cout << "\n\nValid Multisafes Bonus: " << validLocksBonus;
	clock_t end = clock();
	cout << "\nTime taken" << double(end - start) / CLOCKS_PER_SEC;
	datafile.close();
	int x;
	cin >> x;

	delete[] root;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

    return 0;
}

