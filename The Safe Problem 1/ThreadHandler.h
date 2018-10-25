#pragma once
#include "LockCracker.h"
#include <thread>

class ThreadHandler
{
public:
	ThreadHandler();
	~ThreadHandler();
	void RunThreads();
	void AddCracker(LockCracker& cracker) { crackers.push_back(cracker); }
	void CleanCrackers() { crackers.clear(); }
	void CleanThreads() { for (int i = 0; i < threads.size(); i++) { delete threads[i]; } }
	LockCracker& GetCracker(int position) { return crackers[position]; }
private:
	vector<thread*> threads;
	vector<LockCracker> crackers;
	void JoinAllThreads();
};

