#include "stdafx.h"
#include "CombinationLock.h"

CombinationLock::CombinationLock(int Size, int Root[])
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