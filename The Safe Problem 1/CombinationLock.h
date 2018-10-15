#pragma once

class CombinationLock
{
public:
	CombinationLock();
	~CombinationLock();
	int GetROOT() const { return ROOT; }
	int GetCN() const { return CN; }
	int GetLN() const { return LN; }
	int GetHN() const { return LN; }
	void SetROOT(const int value) { ROOT = value; }
	void SetCN(const int value) { CN = value; }
	void SetLN(const int value) { LN = value; }
	void SetHN(const int value) { HN = value; }
private:
	int ROOT;
	int CN;
	int LN;
	int HN;
};