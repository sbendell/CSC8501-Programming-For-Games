#include "stdafx.h"
#include "LockCracker.h"

LockCracker::LockCracker(int* Root, vector<int*> LNs)
{
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
	for (int i = 0; i < lc.validSolutions.size(); i++)
	{
		ostr << "Candidate Solution " << i << "\n" << lc.validSolutions[i];
	}
	return ostr;
}

void LockCracker::SetHash(int* hash, int first, int second, int third, int fourth) {
	while (first < 0) {
		first = first + 10;
	}
	while (second < 0) {
		second = second + 10;
	}
	while (third < 0) {
		third = third + 10;
	}
	while (fourth < 0) {
		fourth = fourth + 10;
	}
	hash[0] = first;
	hash[1] = second;
	hash[2] = third;
	hash[3] = fourth;
}

bool LockCracker::CrackAllCN() {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				for (int l = 0; l < 10; l++)
				{
					SetHash(hashes.UHF, i, j, k, l);
					SetHash(hashes.LHF, UHFLHF[0] - i, UHFLHF[1] - j, UHFLHF[2] - k, UHFLHF[3] - l);
					for (int x = 0; x < crackSafe.GetSize(); x++)
					{
						crackSafe.GetLock(x).SetCN(crackSafe.GetLock(x).GetROOT(0) + hashes.UHF[0], 0);
						crackSafe.GetLock(x).SetCN(crackSafe.GetLock(x).GetROOT(1) + hashes.UHF[1], 1);
						crackSafe.GetLock(x).SetCN(crackSafe.GetLock(x).GetROOT(2) + hashes.UHF[2], 2);
						crackSafe.GetLock(x).SetCN(crackSafe.GetLock(x).GetROOT(3) + hashes.UHF[3], 3);
					}
					if (crackSafe.IsValid()) {
						validSolutions.push_back(crackSafe);
						validHashes.push_back(hashes);
					}
				}
			}
		}
	}
	return false;
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
		UHFLHF[i] = crackSafe.GetLock(0).GetLN(i) - crackSafe.GetLock(0).GetROOT(i);
		while (UHFLHF[i] < 0) {
			UHFLHF[i] = UHFLHF[i] + 10;
		}
		PHF[i] = totalHash[i] - UHFLHF[i];
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
			if (i > 0) {
				crackSafe.GetLock(i).SetROOT(crackSafe.GetLock(i-1).GetHN(x), x);
			}
		}
	}
}

void LockCracker::CrackSafe()
{
	CrackPHF();
	CrackAllHN();
	CrackAllCN();
}
