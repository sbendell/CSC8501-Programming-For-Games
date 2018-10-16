// The Safe Problem 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MultiLockSafe.h"
#include <iostream>
#include <time.h>
#include <random>

using namespace std;

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
	int* UHF = RandomArray(4, 9, -9);
	int* LHF = RandomArray(4, 9, -9);
	int* PHF = RandomArray(4, 9, -9);

	MultiLockSafe firstSafe(1, 4, root, UHF, LHF, PHF);

	int x;
	cin >> x;

	delete[] root;
	delete[] UHF;
	delete[] LHF;
	delete[] PHF;

    return 0;
}

