#pragma once
class CombinationLock
{
public:
	CombinationLock();
	~CombinationLock();
	int GetROOT() const;
	int GetCN() const;
	int GetLN() const;
	int GetHN() const;
private:
	int ROOT;
	int CN;
	int LN;
	int HN;
};

