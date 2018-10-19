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

void OutputToKeyFile(vector<int>& roots, int lockSize, int* UHF, int* LHF, int* PHF, string filename, ofstream& stream) {
	stream.open(filename.c_str());

	stream << "NS " << roots.size() << endl;
	for (int i = 0; i < roots.size(); i++)
	{
		if (roots[i] < 1000) {
			stream << "0" << roots[i] << endl;
		}
		else {
			stream << roots[i] << endl;
		}
		OutputHash(UHF, lockSize, stream);
		OutputHash(LHF, lockSize, stream);
		OutputHash(PHF, lockSize, stream);
	}
	stream.close();
}

void ReadFromKeyFile(string filename, ifstream& stream, char& buffer) {
	stream.open(filename.c_str());
	
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

	vector<int> roots;
	roots.reserve(iterations / 20);
	int validLocks = 0;
	int validLocksBonus = 0;
	string filename = "key.txt";
	ofstream datafile;

	for (int i = 0; i < iterations; i++)
	{
		MultiLockSafe newSafe(safeSize, lockSize, root, UHF, LHF, PHF);
		if (newSafe.IsValid()) {
			validLocks++;
			roots.push_back(ArrayToInt(lockSize, root));
		}
		if (newSafe.IsValidBonus()) {
			validLocksBonus++;
		}

		delete[] root;
		root = RandomArray(lockSize, 9, 0);
	}
	OutputToKeyFile(roots, lockSize, UHF, LHF, PHF, filename, datafile);

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

