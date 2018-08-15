#include "ThreadPool.h"

//Default Constructor
ThreadPool::ThreadPool()
{
	m_nNumThreads = 1;	
}

ThreadPool::ThreadPool(unsigned nNumThreads)
{
	if(nNumThreads == 0)
		m_nNumThreads = 1;
	else
		nNumThreads = nNumThreads;
}

