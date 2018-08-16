#include "ThreadPool.h"

//Default Constructor
ThreadPool::ThreadPool()
{
	m_nNumThreads = 1;
	m_bIsInitialized = false;
}

ThreadPool::ThreadPool(unsigned nNumThreads)
{
	m_bIsInitialized = false;
	if(nNumThreads == 0)
		m_nNumThreads = 1;
	else
		m_nNumThreads = nNumThreads;
}

//Note:: This function "MUST" be called from the main thread
bool ThreadPool::Init()
{
	if(m_bIsInitialized)
		return true;

	for(unsigned i=0;i<m_nNumThreads;i++)
	{
		m_ThreadPool.emplace_back(Thread(i));
		if(not m_ThreadPool[i].StartThread())
		{
			//Failed to initialize this thread... stop all the threads and exit;
			for(unsigned j=0;j<i;j++)
			{
				m_ThreadPool[j].StopThread();
			}
			return false;
		}
	}

	std::cout<<"ThreadPool initialized successfully"<<std::endl;
	return true;
}

void ThreadPool::AssignTask(string sLog)
{
	if(not m_bIsInitialized)
	{
		return;
	}

	if(m_nNumThreads == 1)
	{
		m_ThreadPool[0].assign(sLog);
		return;
	}

	
	//When we come here, the value of m_nThreadIndex is guaranteed to be between 0 and m_nNumThreads-1
	unsigned nThreadIndex = m_nThreadIndex++; 
	nThreadIndex = nThreadIndex%m_nNumThreads;
	m_ThreadPool.Assign(sLog);
}
