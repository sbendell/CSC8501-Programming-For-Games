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

void OutputHash(int* hash, string hashname, int size, ofstream& stream) {
	for (int i = 0; i < size; i++)
	{
		if (i == 0) {
			stream << hashname << hash[i];
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
		OutputHash(UHF, "UHF ", lockSize, stream);
		OutputHash(LHF, "LHF ", lockSize, stream);
		OutputHash(PHF, "PHF", lockSize, stream);
	}
	stream.close();
}

int ReadKeyFileSize(ifstream& stream) {
	string str;
	int temp;
	stream >> str;
	stream >> temp;
	return temp;
}

void ParseHashes(int* hash, ifstream& stream) {
	string str;
	char c;
	stream >> str;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0) {
			stream >> hash[i];
		}
		else {
			stream >> c;
			stream >> hash[i];
		}
	}
}

void ReadSafeFromKeyFile(int* root, int* UHF, int* LHF, int* PHF, ifstream& istream, ofstream& ostream, int iteration) {
	string str;
	char c;
	int tempRoot;
	for (int i = 0; i < 4; i++)
	{
		istream >> c;
		root[i] = (int)c - 48;
	}
	ParseHashes(UHF, istream);
	ParseHashes(LHF, istream);
	ParseHashes(PHF, istream);
	MultiLockSafe readMultiSafe(5, 4, root, UHF, LHF, PHF);
	ostream << "NS" << iteration << " ";
	ostream << readMultiSafe;
}

void ReadFromKeyFile(int* root, int* UHF, int* LHF, int* PHF, string keyfile, string safefile, ifstream& idatafile, ofstream& odatafile){
	idatafile.open(keyfile.c_str());
	odatafile.open(safefile.c_str());
	int keyFileSize = ReadKeyFileSize(idatafile);

	for (int i = 0; i < keyFileSize; i++)
	{
		ReadSafeFromKeyFile(root, UHF, LHF, PHF, idatafile, odatafile, i);
	}
	idatafile.close();
	odatafile.close();
}

int main()
{
	srand(time(NULL));
	clock_t start = clock();
	int* root = RandomArray(4, 9, 0);
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	int iterations = 100000;
	int safeSize = 5;
	int lockSize = 4;

	vector<int> roots;
	roots.reserve(iterations);
	int validLocks = 0;
	int validLocksBonus = 0;
	string keyfile = "key.txt";
	string safefile = "multi-safe.txt";
	ofstream odatafile;
	ifstream idatafile;

	for (int i = 0; i < iterations; i++)
	{
		MultiLockSafe newSafe(safeSize, lockSize, root, UHF, LHF, PHF);
		roots.push_back(ArrayToInt(lockSize, root));
		if (newSafe.IsValid()) {
			validLocks++;
		}
		if (newSafe.IsValidBonus()) {
			validLocksBonus++;
		}

		delete[] root;
		root = RandomArray(lockSize, 9, 0);
	}
	OutputToKeyFile(roots, lockSize, UHF, LHF, PHF, keyfile, odatafile);
	ReadFromKeyFile(root, UHF, LHF, PHF, keyfile, safefile, idatafile, odatafile);

	cout << "Valid Multisafes: " << validLocks;
	cout << "\nValid Multisafes Bonus: " << validLocksBonus;
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

