#pragma once
#include "CombinationLock.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

class MultiLockSafe
{
public:
	MultiLockSafe(int Size, int lockSize, int* root, int* UHF, int*LHF, int* PHF);
	MultiLockSafe(int Size);
	MultiLockSafe();
	~MultiLockSafe();
	//void UnlockHash(CombinationLock* lock, int* hash);
	//void LockHash(CombinationLock* lock, int* hash);
	//void PassHash(CombinationLock* lock, int* hash);
	template<typename T>
	void Hash(int whichlock, int* hash,  T &lambda);
	int GetSize() const { return size; }
	CombinationLock& GetLock(int id) { return locks[id]; }
	friend ostream& operator<<(ostream& ostr, const MultiLockSafe& mls);
	bool IsValid() const;
	bool IsValidBonus();
	string LNOutput();
private:
	vector<CombinationLock> locks;
	int size;
	int* UHF;
	int* LHF;
	int* PHF;
};

