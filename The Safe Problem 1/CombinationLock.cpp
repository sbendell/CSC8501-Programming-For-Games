#include "stdafx.h"
#include "CombinationLock.h"

CombinationLock::CombinationLock(int Size, int* Root)
{
	size = Size;
	for (int i = 0; i < size; i++)
	{
		ROOT[i] = Root[i];
	}
}

CombinationLock::CombinationLock()
{
}

CombinationLock::~CombinationLock()
{
}

void CombinationLock::SetROOT(const int value, const int position) {
	int newVal = value;
	while (newVal > 9) {
		newVal -= 10;
	}
	while (newVal < 0) {
		newVal += 10;
	}
	ROOT[position] = newVal;
}

void CombinationLock::SetCN(const int value, const int position) {
	int newVal = value;
	while (newVal > 9) {
		newVal -= 10;
	}
	while (newVal < 0) {
		newVal += 10;
	}
	CN[position] = newVal;
}

void CombinationLock::SetLN(const int value, const int position) {
	int newVal = value;
	while (newVal > 9) {
		newVal -= 10;
	}
	while (newVal < 0) {
		newVal += 10;
	}
	LN[position] = newVal;
}

void CombinationLock::SetHN(const int value, const int position) {
	int newVal = value;
	while (newVal > 9) {
		newVal -= 10;
	}
	while (newVal < 0) {
		newVal += 10;
	}
	HN[position] = newVal;
}