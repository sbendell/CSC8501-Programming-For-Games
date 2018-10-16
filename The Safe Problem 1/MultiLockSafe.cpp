#include "stdafx.h"
#include "MultiLockSafe.h"


MultiLockSafe::MultiLockSafe(int size, int locksize, int* root, int* Uhf, int* Lhf, int* Phf)
{
	locks = new CombinationLock[size];
	for (int i = 0; i < size; i++)
	{
		locks[i] = CombinationLock(locksize, root);
	}
	UHF = Uhf;
	LHF = Lhf;
	PHF = Phf;
}


MultiLockSafe::~MultiLockSafe()
{
}

void MultiLockSafe::UnlockHash(CombinationLock* lock, int* hash) {
	for (int i = 0; i < lock->GetSize(); i++)
	{
		lock->SetCN(lock->GetROOT(i) + hash[i], i);
	}
}

void MultiLockSafe::LockHash(CombinationLock* lock, int* hash) {
	for (int i = 0; i < lock->GetSize(); i++)
	{
		lock->SetLN(lock->GetCN(i) + hash[i], i);
	}
}

void MultiLockSafe::PassHash(CombinationLock* lock, int* hash) {
	for (int i = 0; i < lock->GetSize(); i++)
	{
		lock->SetHN(lock->GetLN(i) + hash[i], i);
	}
}
