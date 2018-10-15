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
private:
	int ROOT;
	int CN;
	int LN;
	int HN;
};