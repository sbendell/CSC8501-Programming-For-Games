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
	LockCracker(MultiLockSafe safe, int* Root, vector<int*> LNs);
	LockCracker();
	~LockCracker();
	friend ostream& operator<<(ostream& ostr, const LockCracker& lc);
	Hashes& GetHashes() { return hashes; }
private:
	void CrackSafe();
	void CrackAllCN();
	void CrackUHF();
	void CrackLHF();
	void CrackPHF();
	void CrackAllHN();
	bool CrackFirstLockCN();
	MultiLockSafe crackSafe;
	MultiLockSafe realSafe;
	Hashes hashes;
};

