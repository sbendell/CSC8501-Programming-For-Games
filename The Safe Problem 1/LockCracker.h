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
	LockCracker(int* Root, vector<int[]> LNs);
	LockCracker();
	~LockCracker();
private:
	MultiLockSafe safe;
};

