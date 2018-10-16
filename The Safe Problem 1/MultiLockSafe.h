#pragma once
#include "CombinationLock.h"

class MultiLockSafe
{
public:
	MultiLockSafe(int size, int locksize, int* root);
	~MultiLockSafe();
private:
	CombinationLock* locks;
	int* UHF;
	int* LHF;
	int* PHF;
};

