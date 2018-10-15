#include "stdafx.h"
#include "CombinationLock.h"

CombinationLock::CombinationLock(int size, int Root[])
{
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