#include "stdafx.h"
#include "ThreadHandler.h"


ThreadHandler::ThreadHandler()
{
	threads.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		thread* newThread;
		threads.push_back(newThread);
	}
}


ThreadHandler::~ThreadHandler()
{
}

void ThreadHandler::JoinAllThreads() {
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i]->join();
	}
}

void Crack(LockCracker& cracker) {
	cracker.CrackSafe();
}

void ThreadHandler::RunThreads() {
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i] = new thread(Crack, std::ref(crackers[i]));
	}
	JoinAllThreads();
}