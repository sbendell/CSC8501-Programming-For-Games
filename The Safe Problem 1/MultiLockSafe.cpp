#include "stdafx.h"
#include "MultiLockSafe.h"
#include <cmath>

MultiLockSafe::MultiLockSafe(int Size, int lockSize, int* root, int* Uhf, int* Lhf, int* Phf)
{
	size = Size;
	locks = new CombinationLock*[size];
	UHF = Uhf;
	LHF = Lhf;
	PHF = Phf;

	int * nextRoot = root;

	for (int i = 0; i < size; i++)
	{
		locks[i] = new CombinationLock(lockSize, nextRoot);
		UnlockHash(locks[i], UHF);
		LockHash(locks[i], LHF);
		PassHash(locks[i], PHF);
		for (int x = 0; x < lockSize; x++)
		{
			nextRoot[x] = locks[i]->GetHN()[x];
		}
	}
}


MultiLockSafe::~MultiLockSafe()
{
	for (int i = 0; i < size; i++)
	{
		delete locks[i];
	}
	delete[] locks;
}

ostream& operator<<(ostream& ostr, const MultiLockSafe& mls) {
	ostr << "UHF: ";
	for (int i = 0; i < 4; i++)
	{
		ostr << mls.UHF[i] << " ";
	}

	ostr << "\nLHF: ";
	for (int i = 0; i < 4; i++)
	{
		ostr << mls.LHF[i] << " ";
	}

	ostr << "\nPHF: ";
	for (int i = 0; i < 4; i++)
	{
		ostr << mls.PHF[i] << " ";
	}

	for (int i = 0; i < mls.size; i++)
	{
		ostr << *mls.locks[i] << "\n\n";
	}

	ostr << "Multisafe Valid? " << mls.IsValid() << "\n\n";
	return ostr;
}

void MultiLockSafe::UnlockHash(CombinationLock* lock, int* hash) {
	for (int i = 0; i < lock->GetSize(); i++)
	{
		lock->SetCN(lock->GetROOT()[i] + hash[i], i);
	}
}

void MultiLockSafe::LockHash(CombinationLock* lock, int* hash) {
	for (int i = 0; i < lock->GetSize(); i++)
	{
		lock->SetLN(lock->GetCN()[i] + hash[i], i);
	}
}

void MultiLockSafe::PassHash(CombinationLock* lock, int* hash) {
	for (int i = 0; i < lock->GetSize(); i++)
	{
		lock->SetHN(lock->GetLN()[i] + hash[i], i);
	}
}

bool MultiLockSafe::IsValid() const {
	bool valid = true;
	for (int i = 0; i < size; i++)
	{
		if (locks[i]->IsValid() == false) {
			valid = false;
		}
	}
	return valid;
}

bool MultiLockSafe::IsValidBonus() const {
	for (int i = 0; i < size; i++)
	{
		if (locks[i]->IsValid() == false) {
			return false;
		}
	}

	for (int i = 0; i < size - 1; i++)
	{
		if (locks[i]->GetSum() >= locks[i+1]->GetSum()) {
			return false;
		}
	}

	int totalSum = 0;

	for (int i = 0; i < size; i++)
	{
		totalSum += locks[i]->GetSum();
	}

	if (totalSum % 2 == 1) {
		return false;
	}

	return true;
}
