#include "stdafx.h"
#include "CombinationLock.h"


CombinationLock::CombinationLock(int Size, int* Root, int ID)
{
	size = Size;
	id = ID;
	for (int i = 0; i < size; i++)
	{
		SetROOT(Root[i],i);
	}
}

CombinationLock::CombinationLock()
{
}

CombinationLock::~CombinationLock()
{
}

ostream& operator<<(ostream& ostr, const CombinationLock& cl) {
	ostr << "CN" << cl.GetID() << " " << cl.GetCN(0) << cl.GetCN(1) << cl.GetCN(2) << cl.GetCN(3) << ", "
		<< "LN" << cl.GetID() << " " << cl.GetLN(0) << cl.GetLN(1) << cl.GetLN(2) << cl.GetLN(3) << ", "
		<< "HN" << cl.GetID() << " " << cl.GetHN(0) << cl.GetHN(1) << cl.GetHN(2) << cl.GetHN(3);
	return ostr;
}

/*ostream& operator<<(ostream& ostr, const CombinationLock& cl) {
	ostr << "CN ";
	for (int i = 0; i < cl.GetSize(); i++)
	{
		ostr << cl.GetCN(i);
	}

	ostr << ", LN";
	for (int i = 0; i < cl.GetSize(); i++)
	{
		ostr << cl.GetLN(i);
	}

	ostr << ", HN";
	for (int i = 0; i < cl.GetSize(); i++)
	{
		ostr << cl.GetHN(i);
	}
	return ostr;
}*/

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

bool CombinationLock::IsValid() const {
	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			if (i != k) {
				if (CN[i] == CN[k]) {
					return  false;
				}
			}
		}
	}
	return true;
}

int CombinationLock::GetSum() {
	int sum = 0;

	for (int i = 0; i < size; i++)
	{
		sum += CN[i];
	}

	return sum;
}