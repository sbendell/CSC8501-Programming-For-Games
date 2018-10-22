#include "stdafx.h"
#include "MultiLockSafe.h"

MultiLockSafe::MultiLockSafe(int Size, int lockSize, int* root, int* Uhf, int* Lhf, int* Phf)
{
	size = Size;
	UHF = Uhf;
	LHF = Lhf;
	PHF = Phf;

	for (int i = 0; i < size; i++)
	{
		locks[i] = CombinationLock(lockSize, root, i);
		//UnlockHash(locks[i], UHF);
		//LockHash(locks[i], LHF);
		//PassHash(locks[i], PHF);
		Hash(i, UHF, [](int iterator, CombinationLock& lock, int* hash) { lock.SetCN(lock.GetROOT(iterator) + hash[iterator], iterator); });
		Hash(i, LHF, [](int iterator, CombinationLock& lock, int* hash) { lock.SetLN(lock.GetCN(iterator) + hash[iterator], iterator); });
		Hash(i, PHF, [](int iterator, CombinationLock& lock, int* hash) { lock.SetHN(lock.GetLN(iterator) + hash[iterator], iterator); });
		for (int x = 0; x < lockSize; x++)
		{
			root[x] = locks[i].GetHN(x);
		}
	}
}

MultiLockSafe::MultiLockSafe() {

}

MultiLockSafe::~MultiLockSafe()
{
}

ostream& operator<<(ostream& ostr, const MultiLockSafe& mls) {
	if (mls.IsValid()) {
		ostr << "VALID" << "\n";
	}
	else {
		ostr << "NOT VALID" << "\n";
	}

	for (int i = 0; i < mls.size; i++)
	{
		ostr << mls.locks[i] << "\n";
	}
	ostr << "\n";
	return ostr;
}

template <typename T>
void MultiLockSafe::Hash(int whichlock, int* hash, T &lambda) {
	for (int i = 0; i < locks[0].GetSize(); i++)
	{
		lambda(i, locks[whichlock], hash);
	}
}

/*
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
}*/

bool MultiLockSafe::IsValid() const {
	for (int i = 0; i < size; i++)
	{
		if (locks[i].IsValid() == false) {
			return false;
		}
	}
	return true;
}

bool MultiLockSafe::IsValidBonus() {
	for (int i = 0; i < size; i++)
	{
		if (locks[i].IsValid() == false) {
			return false;
		}
	}

	for (int i = 0; i < size - 1; i++)
	{
		if (locks[i].GetSum() >= locks[i+1].GetSum()) {
			return false;
		}
	}

	int totalSum = 0;

	for (int i = 0; i < size; i++)
	{
		totalSum += locks[i].GetSum();
	}

	if (totalSum % 2 == 1) {
		return false;
	}

	return true;
}
