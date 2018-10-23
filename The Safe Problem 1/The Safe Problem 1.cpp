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
#include "FileHandler.h"

using namespace std;

int* RandomArray(int size, int upperbound, int lowerbound) {
	int* newArray = new int[size];
	if (lowerbound < 0) {
		upperbound = upperbound + abs(lowerbound);
	}
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

void ValidateSafes(int iterationCap, int validLocks, int safeSize, int lockSize, int*& root, int*& tempRoot, int*& UHF, int*& LHF,
	int*& PHF, vector<int>& roots, int& validLocksBonus) {
	int iterations = 0;
	while(roots.size() < validLocks && iterations < iterationCap)
	{
		for (int x = 0; x < lockSize; x++)
		{
			tempRoot[x] = root[x];
		}

		MultiLockSafe newSafe(safeSize, lockSize, tempRoot, UHF, LHF, PHF);
		if (newSafe.IsValid()) {
			roots.push_back(ArrayToInt(lockSize, root));
			validLocks++;
		}
		if (newSafe.IsValidBonus()) {
			validLocksBonus++;
		}

		delete[] root;
		root = RandomArray(lockSize, 9, 0);
		iterations++;
	}
}

int main()
{
	srand(time(NULL));
	clock_t start = clock();
	int* root = RandomArray(4, 9, 0);
	int* tempRoot = new int[4];
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	int iterationCap = 100000;
	int safeSize = 5;
	int lockSize = 4;
	int validLocks = 100;
	int validLocksBonus = 0;

	vector<int> roots;
	roots.reserve(validLocks);
	string keyfile = "key.txt";
	string safefile = "multi-safe.txt";
	ofstream odatafile;
	ifstream idatafile;
	ValidateSafes(iterationCap, validLocks, safeSize, lockSize, root, tempRoot, UHF, LHF, PHF, roots, validLocksBonus);
	if (roots.size() >= validLocks) {
		OutputToKeyFile(roots, lockSize, UHF, LHF, PHF, keyfile, odatafile);
		ReadFromKeyFile(root, UHF, LHF, PHF, keyfile, safefile, idatafile, odatafile);
		cout << "Valid Multisafes: " << validLocks;
		cout << "\nValid Multisafes Bonus: " << validLocksBonus;
	}
	else {
		cout << "Did not find " << validLocks << " valid locks in " << iterationCap << " iterations.";
	}

	clock_t end = clock();
	cout << "\nTime taken" << double(end - start) / CLOCKS_PER_SEC;
	int x;
	cin >> x;

	delete[] root;
	delete[] tempRoot;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

	return 0;
}

