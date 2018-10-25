#pragma once
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

struct Hashes {
	int UHF[4];
	int LHF[4];
	int PHF[4];
};

class LockCracker
{
public:
	LockCracker(int* Root, vector<int*> LNs);
	LockCracker();
	~LockCracker();
	friend ostream& operator<<(ostream& ostr, const LockCracker& lc);
	Hashes& GetHashes() { return hashes; }
	vector<MultiLockSafe> validSolutions;
	vector<Hashes> validHashes;
	void CrackSafe();
private:
	void SetHash(int hash[4], int first, int second, int third, int fourth);
	bool CrackAllCN();
	void CrackPHF();
	void CrackAllHN();
	MultiLockSafe crackSafe;
	Hashes hashes;
	int UHFLHF[4];
};

