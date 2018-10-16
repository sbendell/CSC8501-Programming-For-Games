#pragma once

class CombinationLock
{
public:
	CombinationLock(int size, int Root[]);
	CombinationLock();
	~CombinationLock();
	int GetROOT(const int position) const { return ROOT[position]; }
	int GetCN(const int position) const { return CN[position]; }
	int GetLN(const int position) const { return LN[position]; }
	int GetHN(const int position) const { return HN[position]; }
	int GetSize() const { return size; }
	void SetROOT(const int value, const int position) { ROOT[position] = value; }
	void SetCN(const int value, const int position) { CN[position] = value; }
	void SetLN(const int value, const int position) { LN[position] = value; }
	void SetHN(const int value, const int position) { HN[position] = value; }
private:
	int size;
	int ROOT[4];
	int CN[4];
	int LN[4];
	int HN[4];
};