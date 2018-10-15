// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CombinationLock.h"
#include <iostream>

using namespace std;

void UnlockHash(CombinationLock& lock) {
	int hash[4] = { +1, -1, +1, -1 };

	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetCN(lock.GetROOT(i) + hash[i], i);
	}
}

void LockHash(CombinationLock& lock) {
	int hash[4] = { +1, -1, +1, -1 };

	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetLN(lock.GetCN(i) + hash[i], i);
	}
}

void PassHash(CombinationLock& lock) {
	int hash[4] = { +1, -1, +1, -1 };

	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetHN(lock.GetLN(i) + hash[i], i);
	}
}

int main()
{
	int arr[4] = { 6, 7, 8, 9 };
	CombinationLock firstLock(4, arr);

	UnlockHash(firstLock);
	LockHash(firstLock);
	PassHash(firstLock);

	cout << "Root: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetROOT(i);
	}

	cout << "\nCN: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetCN(i);
	}

	cout << "\nLN: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetLN(i);
	}

	cout << "\nHN: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetHN(i);
	}

	int x;
	cin >> x;

    return 0;
}

