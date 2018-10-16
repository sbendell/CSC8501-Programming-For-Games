#include "stdafx.h"
#include "MultiLockSafe.h"


MultiLockSafe::MultiLockSafe(int size, int locksize, int* root)
{
	locks = new CombinationLock[size];
	for (int i = 0; i < size; i++)
	{
		locks[i] = CombinationLock(locksize, root);
	}
}


MultiLockSafe::~MultiLockSafe()
{
}
