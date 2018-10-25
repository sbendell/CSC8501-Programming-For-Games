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
#include "LockCracker.h"

using namespace std;

void RandomArray(int* arrPtr, int size, int upperbound, int lowerbound) {
	if (lowerbound < 0) {
		upperbound = upperbound + abs(lowerbound);
	}
	for (int i = 0; i < size; i++)
	{
		arrPtr[i] = rand() % (upperbound + 1) + lowerbound;
	}
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
		RandomArray(root, lockSize, 9, 0);
		for (int x = 0; x < lockSize; x++)
		{
			tempRoot[x] = root[x];
		}

		MultiLockSafe newSafe(safeSize, lockSize, tempRoot, UHF, LHF, PHF);
		if (newSafe.IsValid()) {
			roots.push_back(ArrayToInt(lockSize, root));
		}
		if (newSafe.IsValidBonus()) {
			validLocksBonus++;
		}
		iterations++;
	}
}

void GenerateNewHashes(int* UHF, int* LHF, int* PHF, int lockSize) {
	RandomArray(UHF, lockSize, 9, 0);
	RandomArray(LHF, lockSize, 9, 0);
	RandomArray(PHF, lockSize, 9, 0);
}

int main()
{
	srand(time(NULL));
	int* root = new int[4];
	int* tempRoot = new int[4];
	int* UHF = new int[4];
	int* LHF = new int[4];
	int* PHF = new int[4];

	int iterationCap = 10000;
	int safeSize = 5;
	int lockSize = 4;
	int validLocks = 100;
	int validLocksBonus = 0;

	bool runAgain = true;
	bool generate = true;

	vector<int> roots;
	roots.reserve(validLocks);
	string keyfile = "key.txt";
	string safefile = "multi-safe.txt";
	string lockedfile = "locked-safe.txt";
	string crackedkeyfile = "cracked-key.txt.";
	string crackedsafefile = "cracked-safe.txt.";

	while (runAgain) {
		char c;
		cout << "Should I generate or hack safes? g/h";
		cin >> c;
		if (c == 'g') {
			generate = true;
		}
		else if (c == 'h') {
			generate = false;
		}
		if(generate) {
			cout << "How many solutions should I find?\n";
			cin >> validLocks;
			cout << "How many locks per safe?\n";
			cin >> safeSize;
			clock_t start = clock();
			GenerateNewHashes(UHF, LHF, PHF, lockSize);
			ValidateSafes(iterationCap, validLocks, safeSize, lockSize, root, tempRoot, UHF, LHF, PHF, roots, validLocksBonus);
			if (roots.size() > 0) {
				OutputToKeyFile(roots, lockSize, UHF, LHF, PHF, keyfile);
				ReadFromKeyFile(root, safeSize, lockSize, UHF, LHF, PHF, keyfile, safefile, lockedfile, roots.size());
				cout << "Valid Multisafes: " << validLocks;
				cout << "\nValid Multisafes Bonus: " << validLocksBonus;
			}
			else {
				cout << "Did not find " << validLocks << " valid locks in " << iterationCap << " iterations.";
			}

			clock_t end = clock();
			cout << "\nTime taken " << double(end - start) / CLOCKS_PER_SEC << "ms";
		}
		else {
			clock_t start = clock();
			ReadSafeToHack(lockedfile, crackedkeyfile, crackedsafefile);
			cout << "Cracked all safes within given locked safe file.\n";
			clock_t end = clock();
			cout << "\nTime taken " << double(end - start) / CLOCKS_PER_SEC << "ms";
		}
		roots.clear();
		cout << "\n\nWould you like to run again? y/n\n";
		cin >> c;
		if (c == 'y') {
			runAgain = true;
		}
		else if (c == 'n') {
			runAgain = false;
		}
	}
	delete[] tempRoot;
	delete[] root;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

	return 0;
}

