#pragma once
#include "CombinationLock.h"

class MultiLockSafe
{
public:
	MultiLockSafe(int size, int locksize, int* root, int* UHF, int*LHF, int* PHF);
	~MultiLockSafe();
	void UnlockHash(CombinationLock* lock, int* hash);
	void LockHash(CombinationLock* lock, int* hash);
	void PassHash(CombinationLock* lock, int* hash);
private:
	CombinationLock* locks;
	int* UHF;
	int* LHF;
	int* PHF;
};

