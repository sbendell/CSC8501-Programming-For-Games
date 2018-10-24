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

void OutputToKeyFile(vector<int>& roots, int lockSize, int* UHF, int* LHF, int* PHF, string filename) {
	ofstream stream;
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

void ReadSafeFromKeyFile(int* root, int safeSize, int lockSize, int* UHF, int* LHF, int* PHF,
	ifstream& keyfilestream, ofstream& safefilestream, ofstream& lockedfilestream, int iteration) {
	string str;
	char c;
	for (int i = 0; i < 4; i++)
	{
		keyfilestream >> c;
		root[i] = (int)c - 48;
	}
	ParseHashes(UHF, keyfilestream);
	ParseHashes(LHF, keyfilestream);
	ParseHashes(PHF, keyfilestream);
	MultiLockSafe readMultiSafe(safeSize, lockSize, root, UHF, LHF, PHF);
	safefilestream << "NS" << iteration << " ";
	safefilestream << readMultiSafe;
	lockedfilestream << readMultiSafe.LNOutput();
}

void ReadFromKeyFile(int* root, int safeSize, int lockSize, int* UHF, int* LHF, int* PHF,
	string keyfile, string safefile, string lockedfile, int validSafes) {
	ifstream keyfilestream;
	ofstream safefilestream;
	ofstream lockedfilestream;

	keyfilestream.open(keyfile.c_str());
	safefilestream.open(safefile.c_str());
	lockedfilestream.open(lockedfile.c_str());

	int keyFileSize = ReadKeyFileSize(keyfilestream);
	lockedfilestream << "NL " << validSafes << "\n";
	for (int i = 0; i < keyFileSize; i++)
	{
		ReadSafeFromKeyFile(root, safeSize, lockSize, UHF, LHF, PHF, keyfilestream, safefilestream, lockedfilestream, i);
	}

	keyfilestream.close();
	safefilestream.close();
	lockedfilestream.close();
}