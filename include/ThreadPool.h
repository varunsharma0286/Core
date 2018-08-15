/*
 *This is a generic implementation of Thread pools 
 *using C++11
 *To use this ThreadPool, create
 *1) Create a ThreadPool object
 *2) Call the Init from the main thread;
 *3) Assign a task to ThreadPool using AssignTask call
 */

#include<thread>
#include<iostream>



#ifndef _THREADPOOL_H
#define _THREADPOOL_H

//This Thread will be used by "ThreadPool"
struct Thread
{
	std::thread mThread;
	std::queue<string> mQueue;
	void Assign(string sLog)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		mQueue.push_back(sLog);
	}
	
	void Run()
	{
		
	}

	std::mutex m_Mutex;
}

class ThreadPool
{
public:
	ThreadPool();

	ThreadPool(unsigned nNumThreads);

	bool Init();

	void AssignTask();
	//void ResizeThreadPool(unsigned nNumThreads)
	
private:
	unsigned m_nNumThreads;
	vector<Thread> m_ThreadPool; 
	bool m_bIsInitialized;
	atomic<unsigned> m_nThreadIndex = 0; //Initialized to point to first thread;
};

#endif
