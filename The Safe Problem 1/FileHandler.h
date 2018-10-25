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
#include "ThreadHandler.h"

using namespace std;

void OutputHash(int* hash, string hashname, int size, ofstream& stream) {
	for (int i = 0; i < size; i++)
	{
		if (i == 0) {
			if (hash[i] >= 0) {
				stream << hashname << '+' << hash[i];
			}
			else {
				stream << hashname << hash[i];
			}
		}
		else {
			if (hash[i] >= 0) {
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
		stream << "ROOT ";
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
				hash[i] = hash[i] + 10;
			}
		}
		else {
			stream >> c;
			stream >> c;
			stream >> hash[i];
			if (c == '-') {
				hash[i] = hash[i] + 10;
			}
		}
	}
}

void ReadSafeFromKeyFile(int* root, int safeSize, int lockSize, int* UHF, int* LHF, int* PHF,
	ifstream& keyfilestream, ofstream& safefilestream, ofstream& lockedfilestream, int iteration) {
	string str;
	char c;
	keyfilestream >> str;
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

void WriteCrackedSafesToFile(ofstream& crackedsafestream, ofstream& crackedkeystream, int i, LockCracker cracker) {
	crackedsafestream << "NS" << i << "\n" << cracker;
	for (int x = 0; x < cracker.validSolutions.size(); x++)
	{
		crackedsafestream << "Candidate Solution " << x << "\n" << cracker.validSolutions[x];
		crackedkeystream << "Candidate Solution " << x << "\n";
		crackedkeystream << "ROOT ";
		for (int j = 0; j < 4; j++)
		{
			crackedkeystream << cracker.validSolutions[x].GetLock(0).GetROOT(j);
		}
		crackedkeystream << "\n";
		OutputHash(cracker.validHashes[x].UHF, "UHF ", 4, crackedkeystream);
		OutputHash(cracker.validHashes[x].LHF, "LHF ", 4, crackedkeystream);
		OutputHash(cracker.validHashes[x].PHF, "PHF ", 4, crackedkeystream);
	}
}

void ReadSafeToHack(string lockedfile, string crackedkeyfile, string crackedsafefile) {
	ifstream lockedfilestream;
	ofstream crackedkeystream;
	ofstream crackedsafestream;

	lockedfilestream.open(lockedfile.c_str());
	crackedkeystream.open(crackedkeyfile.c_str());
	crackedsafestream.open(crackedsafefile.c_str());

	ThreadHandler threads;

	int lockedFileSize = ReadKeyFileSize(lockedfilestream);
	crackedkeystream << "NS " << lockedFileSize << "\n";
	for (int i = 0; i < lockedFileSize; i++)
	{
		int crackroot[4];
		string str;
		char c;
		int readval;

		lockedfilestream >> str;
		for (int x = 0; x < 4; x++)
		{
			lockedfilestream >> readval;
			crackroot[x] = readval;
		}

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

		LockCracker cracker(crackroot, LNs);
		threads.AddCracker(cracker);

		if ((i + 1) % 10 == 0) {
			threads.RunThreads();
			for (int k = 0; k < 10; k++)
			{
				WriteCrackedSafesToFile(crackedsafestream, crackedkeystream, i, threads.GetCracker(k));
			}
			threads.CleanCrackers();
			threads.CleanThreads();
		}

		for (int x = 0; x < LNs.size(); x++)
		{
			delete[] LNs[x];
		}
	}
	lockedfilestream.close();
	crackedkeystream.close();
	crackedsafestream.close();
}