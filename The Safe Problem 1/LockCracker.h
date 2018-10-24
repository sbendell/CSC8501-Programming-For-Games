#pragma once
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

class LockCracker
{
public:
	LockCracker(MultiLockSafe safe, int* Root, vector<int*> LNs);
	LockCracker();
	~LockCracker();
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
};

