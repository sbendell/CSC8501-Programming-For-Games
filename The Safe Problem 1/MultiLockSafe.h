#pragma once
#include "CombinationLock.h"

class MultiLockSafe
{
public:
	MultiLockSafe(int Size, int lockSize, int* root, int* UHF, int*LHF, int* PHF);
	MultiLockSafe();
	~MultiLockSafe();
	//void UnlockHash(CombinationLock* lock, int* hash);
	//void LockHash(CombinationLock* lock, int* hash);
	//void PassHash(CombinationLock* lock, int* hash);
	template<typename T>
	void Hash(int whichlock, int* hash,  T &lambda);
	int GetSize() const { return size; }
	friend ostream& operator<<(ostream& ostr, const MultiLockSafe& mls);
	bool IsValid() const;
	bool IsValidBonus();
private:
	CombinationLock locks[5];
	int size;
	int* UHF;
	int* LHF;
	int* PHF;
};

