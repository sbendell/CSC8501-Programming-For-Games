// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CombinationLock.h"

void UnlockHashFunction(CombinationLock lock) {
	int hash[4] = { +1, -1, +1, -1 };

	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetCN(lock.GetROOT(i) + hash[i], i);
	}
}

void LockHashFunction() {

}

void PassHashFunction() {

}

int main()
{
	int arr[4] = { 6, 7, 8, 9 };
	CombinationLock firstLock(4, arr);

    return 0;
}
