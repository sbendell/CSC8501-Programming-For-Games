#include "stdafx.h"
#include "LockCracker.h"


LockCracker::LockCracker(int* Root, vector<int[]> LNs)
{
	MultiLockSafe newSafe;
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
}

LockCracker::LockCracker()
{
}


LockCracker::~LockCracker()
{
}
