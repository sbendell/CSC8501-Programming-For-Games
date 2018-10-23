#pragma once
#include "stdafx.h"
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

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
	stream << "\n";
}

void OutputToKeyFile(vector<int>& roots, int lockSize, int* UHF, int* LHF, int* PHF, string filename, ofstream& stream) {
	stream.open(filename.c_str());

	stream << "NS " << roots.size() << "\n";
	for (int i = 0; i < roots.size(); i++)
	{
		if (roots[i] < 1000) {
			stream << "0" << roots[i] << "\n";
		}
		else if (roots[i] < 100) {
			stream << "00" << roots[i] << "\n";
		}
		else if (roots[i] < 10) {
			stream << "000" << roots[i] << "\n";
		}
		else {
			stream << roots[i] << "\n";
		}
		OutputHash(UHF, "UHF ", lockSize, stream);
		OutputHash(LHF, "LHF ", lockSize, stream);
		OutputHash(PHF, "PHF ", lockSize, stream);
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

void ReadSafeFromKeyFile(int* root, int safeSize, int lockSize, int* UHF, int* LHF, int* PHF, ifstream& istream, ofstream& ostream, int iteration) {
	string str;
	char c;
	for (int i = 0; i < 4; i++)
	{
		istream >> c;
		root[i] = (int)c - 48;
	}
	ParseHashes(UHF, istream);
	ParseHashes(LHF, istream);
	ParseHashes(PHF, istream);
	MultiLockSafe readMultiSafe(safeSize, lockSize, root, UHF, LHF, PHF);
	ostream << "NS" << iteration << " ";
	ostream << readMultiSafe;
}

void ReadFromKeyFile(int* root, int safeSize, int lockSize, int* UHF, int* LHF, int* PHF, string keyfile, string safefile, ifstream& idatafile, ofstream& odatafile) {
	idatafile.open(keyfile.c_str());
	odatafile.open(safefile.c_str());
	int keyFileSize = ReadKeyFileSize(idatafile);

	for (int i = 0; i < keyFileSize; i++)
	{
		ReadSafeFromKeyFile(root, safeSize, lockSize, UHF, LHF, PHF, idatafile, odatafile, i);
	}
	idatafile.close();
	odatafile.close();
}