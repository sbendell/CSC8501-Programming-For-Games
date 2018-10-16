#include "stdafx.h"
#include "MultiLockSafe.h"


MultiLockSafe::MultiLockSafe(int Size, int lockSize, int* root, int* Uhf, int* Lhf, int* Phf)
{
	size = Size;
	locks = new CombinationLock[size];
	for (int i = 0; i < size; i++)
	{
		locks[i] = CombinationLock(lockSize, root);
	}
	UHF = Uhf;
	LHF = Lhf;
	PHF = Phf;
}


MultiLockSafe::~MultiLockSafe()
{
}

ostream& operator<<(ostream& ostr, const MultiLockSafe& mls) {
	for (int i = 0; i < mls.size; i++)
	{
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

		ostr << "\nRoot: ";
		for (int i = 0; i < mls.locks[i].GetSize(); i++)
		{
			ostr << mls.locks[i].GetROOT(i) << " ";
		}

		ostr << "\nCN:   ";
		for (int i = 0; i < mls.locks[i].GetSize(); i++)
		{
			ostr << mls.locks[i].GetCN(i) << " ";
		}

		ostr << "\nLN:   ";
		for (int i = 0; i < mls.locks[i].GetSize(); i++)
		{
			ostr << mls.locks[i].GetLN(i) << " ";
		}

		ostr << "\nHN:   ";
		for (int i = 0; i < mls.locks[i].GetSize(); i++)
		{
			ostr << mls.locks[i].GetHN(i) << " ";
		}

		ostr << "\nValid? " << mls.locks[i].IsValid();
	}
	return ostr;
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
