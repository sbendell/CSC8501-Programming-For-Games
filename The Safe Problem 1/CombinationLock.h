#pragma once
#include <iostream>

using namespace std;

class CombinationLock
{
public:
	CombinationLock(int size, int* Root);
	CombinationLock();
	~CombinationLock();
	int GetROOT(const int position) const { return ROOT[position]; }
	int GetCN(const int position) const { return CN[position]; }
	int GetLN(const int position) const { return LN[position]; }
	int GetHN(const int position) const { return HN[position]; }

	int GetSize() const { return size; }
	void SetROOT(const int value, const int position);
	void SetCN(const int value, const int position);
	void SetLN(const int value, const int position);
	void SetHN(const int value, const int position);
	bool IsValid() const;
	int GetSum();
	friend ostream& operator<<(ostream& ostr, const CombinationLock& cl);
private:
	int size;
	int ROOT[4];
	int CN[4];
	int LN[4];
	int HN[4];

};