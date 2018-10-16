// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CombinationLock.h"
#include <iostream>
#include <time.h>
#include <random>

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

int* RandomArray(int size, int upperbound, int lowerbound) {
	int* newArray = new int[size];
	for (int i = 0; i < size; i++)
	{
		newArray[i] = rand() % (upperbound + 1 - lowerbound) + lowerbound;
	}
	return newArray;
}

int main()
{
	srand(time(NULL));
	int* root = RandomArray(4, 9, 0);
	CombinationLock firstLock(4, root);
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	UnlockHash(firstLock, UHF);
	LockHash(firstLock, LHF);
	PassHash(firstLock, PHF);

	cout << "UHF: ";
	for (int i = 0; i < 4; i++)
	{
		cout << UHF[i] << " ";
	}

	cout << "\nLHF: ";
	for (int i = 0; i < 4; i++)
	{
		cout << LHF[i] << " ";
	}

	cout << "\nPHF: ";
	for (int i = 0; i < 4; i++)
	{
		cout << PHF[i] << " ";
	}

	cout << "\nRoot: ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetROOT(i) << " ";
	}

	cout << "\nCN:   ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetCN(i) << " ";
	}

	cout << "\nLN:   ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetLN(i) << " ";
	}

	cout << "\nHN:   ";
	for (int i = 0; i < firstLock.GetSize(); i++)
	{
		cout << firstLock.GetHN(i) << " ";
	}

	int x;
	cin >> x;

	delete[] root;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

    return 0;
}

