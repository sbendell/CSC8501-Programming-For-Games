#include "stdafx.h"
#include "LockCracker.h"

LockCracker::LockCracker(MultiLockSafe safe, int* Root, vector<int*> LNs)
{
	realSafe = safe;
	MultiLockSafe newSafe(5);
	for (int i = 0; i < 4; i++)
	{
		newSafe.GetLock(0).SetROOT(Root[i], i);
	}

	for (int i = 0; i < LNs.size(); i++)
	{
		for (int x = 0; x < 4; x++)
		{
			newSafe.GetLock(i).SetLN(LNs[i][x], x);
		}
	}
	crackSafe = newSafe;
	CrackSafe();
}

LockCracker::LockCracker()
{
}


LockCracker::~LockCracker()
{
}

ostream& operator<<(ostream& ostr, const LockCracker& lc) {
	ostr << lc.crackSafe;
	return ostr;
}

bool LockCracker::CrackFirstLockCN() {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				for (int h = 0; h < 10; h++)
				{
					if ((realSafe.GetLock(0).GetCN(0) == i && realSafe.GetLock(0).GetCN(1) == j)
						&& (realSafe.GetLock(0).GetCN(2) == k && realSafe.GetLock(0).GetCN(3) == h))
					{
						crackSafe.GetLock(0).SetCN(i, 0);
						crackSafe.GetLock(0).SetCN(j, 1);
						crackSafe.GetLock(0).SetCN(k, 2);
						crackSafe.GetLock(0).SetCN(h, 3);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void LockCracker::CrackAllCN() {
	int LNdifference[4];
	for (int i = 0; i < 4; i++)
	{
		LNdifference[i] = crackSafe.GetLock(1).GetLN(i) - crackSafe.GetLock(0).GetLN(i);
		while (LNdifference[i] < 0) {
			LNdifference[i] = LNdifference[i] + 10;
		}
	}

	for (int i = 1; i < crackSafe.GetSize(); i++)
	{
		for (int x = 0; x < 4; x++)
		{
			crackSafe.GetLock(i).SetCN(crackSafe.GetLock(i-1).GetCN(x) + LNdifference[x], x);
		}
	}
}

void LockCracker::CrackUHF() {
	int UHF[4];
	for (int i = 0; i < 4; i++)
	{
		UHF[i] = crackSafe.GetLock(0).GetCN(i) - crackSafe.GetLock(0).GetROOT(i);
		while (UHF[i] < 0) {
			UHF[i] = UHF[i] + 10;
		}
		hashes.UHF[i] = UHF[i];
	}
}

void LockCracker::CrackLHF() {
	int LHF[4];
	for (int i = 0; i < 4; i++)
	{
		LHF[i] = crackSafe.GetLock(0).GetLN(i) - crackSafe.GetLock(0).GetCN(i);
		while (LHF[i] < 0) {
			LHF[i] = LHF[i] + 10;
		}
		hashes.LHF[i] = LHF[i];
	}
}

void LockCracker::CrackPHF() {
	int PHF[4];
	int totalHash[4];
	for (int i = 0; i < 4; i++)
	{
		totalHash[i] = crackSafe.GetLock(1).GetLN(i) - crackSafe.GetLock(0).GetLN(i);
		while(totalHash[i] < 0) {
			totalHash[i] = totalHash[i] + 10;
		}
		PHF[i] = totalHash[i] - (hashes.UHF[i] + hashes.LHF[i]);
		while(PHF[i] < 0) {
			PHF[i] = PHF[i] + 10;
		}
		hashes.PHF[i] = PHF[i];
	}
}

void LockCracker::CrackAllHN() {
	for (int i = 0; i < crackSafe.GetSize(); i++)
	{
		for (int x = 0; x < 4; x++)
		{
			crackSafe.GetLock(i).SetHN(crackSafe.GetLock(i).GetLN(x) + hashes.PHF[x], x);
		}
	}
}

void LockCracker::CrackSafe()
{
	CrackFirstLockCN();
	CrackAllCN();
	CrackUHF();
	CrackLHF();
	CrackPHF();
	CrackAllHN();
}
