// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CombinationLock.h"
#include <iostream>

using namespace std;

void UnlockHash(CombinationLock& lock, int hash[]) {
	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetCN(lock.GetROOT(i) + hash[i], i);
	}
}

void LockHash(CombinationLock& lock, int hash[]) {
	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetLN(lock.GetCN(i) + hash[i], i);
	}
}

void PassHash(CombinationLock& lock, int hash[]) {
	for (int i = 0; i < lock.GetSize(); i++)
	{
		lock.SetHN(lock.GetLN(i) + hash[i], i);
	}
}

int main()
{
	int root[4] = { 6, 7, 8, 9 };
	CombinationLock firstLock(4, root);
	int hash[4] = { +1, -1, +1, -1 };

	UnlockHash(firstLock, hash);
	LockHash(firstLock, hash);
	PassHash(firstLock, hash);

	cout << "First Lock:\nRoot: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetROOT(i) << " ";
	}

	cout << "\nCN: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetCN(i) << " ";
	}

	cout << "\nLN: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetLN(i) << " ";
	}

	cout << "\nHN: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetHN(i) << " ";
	}

	int newRoot[4] = { firstLock.GetHN(0), firstLock.GetHN(1), firstLock.GetHN(2), firstLock.GetHN(3) };
	CombinationLock secondLock(4, newRoot);
	UnlockHash(secondLock, hash);
	LockHash(secondLock, hash);
	PassHash(secondLock, hash);

	cout << "\n\nSecond Lock:\nRoot: ";
	for (int i = 0; i < secondLock.GetSize(); i++)
	{
		cout << secondLock.GetROOT(i) << " ";
	}

	cout << "\nCN: ";
	for (int i = 0; i < secondLock.GetSize(); i++)
	{
		cout << secondLock.GetCN(i) << " ";
	}

	cout << "\nLN: ";
	for (int i = 0; i < secondLock.GetSize(); i++)
	{
		cout << secondLock.GetLN(i) << " ";
	}

	cout << "\nHN: ";
	for (int i = 0; i < secondLock.GetSize(); i++)
	{
		cout << secondLock.GetHN(i) << " ";
	}

	int x;
	cin >> x;

    return 0;
}

