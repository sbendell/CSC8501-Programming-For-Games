#pragma once
#include "stdafx.h"
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <string>
#include <cmath>
#include "LockCracker.h"

using namespace std;

void OutputHash(int* hash, string hashname, int size, ofstream& stream) {
	for (int i = 0; i < size; i++)
	{
		if (i == 0) {
			if (hash[i] > 0) {
				stream << hashname << '+' << hash[i];
			}
			else {
				stream << hashname << hash[i];
			}
		}
		else {
			if (hash[i] > 0) {
				stream << "," << '+' << hash[i];
			}
			else {
				stream << "," << hash[i];
			}
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
			stream >> c;
			stream >> hash[i];
			if (c == '-') {
				hash[i] = hash[i] * -1;
			}
		}
		else {
			stream >> c;
			stream >> c;
			stream >> hash[i];
			if (c == '-') {
				hash[i] = hash[i] * -1;
			}
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

void ReadSafeToHack(string keyfile, string lockedfile, string crackedkeyfile, string crackedsafefile) {
	ifstream keyfilestream;
	ifstream lockedfilestream;
	ofstream crackedkeystream;
	ofstream crackedsafestream;

	keyfilestream.open(keyfile.c_str());
	lockedfilestream.open(lockedfile.c_str());
	crackedkeystream.open(crackedkeyfile.c_str());
	crackedsafestream.open(crackedsafefile.c_str());

	int keyFileSize = ReadKeyFileSize(keyfilestream);
	int lockedFileSize = ReadKeyFileSize(lockedfilestream);
	crackedkeystream << "NS " << keyFileSize << "\n";
	for (int i = 0; i < keyFileSize; i++)
	{
		int realroot[4];
		int crackroot[4];
		int UHF[4];
		int LHF[4];
		int PHF[4];
		string str;
		char c;
		int readval;

		lockedfilestream >> str;
		for (int x = 0; x < 4; x++)
		{
			keyfilestream >> c;
			realroot[x] = (int)c - 48;
			lockedfilestream >> readval;
			crackroot[x] = readval;
		}
		ParseHashes(UHF, keyfilestream);
		ParseHashes(LHF, keyfilestream);
		ParseHashes(PHF, keyfilestream);

		vector<int*> LNs;
		for (int x = 0; x < 5; x++)
		{
			lockedfilestream >> str;
			int* LN = new int[4];
			for (int y = 0; y < 4; y++)
			{
				lockedfilestream >> readval;
				LN[y] = readval;
			}
			LNs.push_back(LN);
		}

		MultiLockSafe readMultiSafe(5, 4, realroot, UHF, LHF, PHF);
		LockCracker cracker(readMultiSafe, crackroot, LNs);

		for (int i = 0; i < 4; i++)
		{
			crackedkeystream << crackroot[i];
		}
		crackedkeystream << "\n";
		OutputHash(cracker.GetHashes().UHF, "UHF ", 4, crackedkeystream);
		OutputHash(cracker.GetHashes().LHF, "LHF ", 4, crackedkeystream);
		OutputHash(cracker.GetHashes().PHF, "PHF ", 4, crackedkeystream);

		crackedsafestream << "NS" << i << " " << cracker;

		for (int i = 0; i < LNs.size(); i++)
		{
			delete[] LNs[i];
		}
	}

	keyfilestream.close();
	lockedfilestream.close();
	crackedkeystream.close();
	crackedsafestream.close();
}