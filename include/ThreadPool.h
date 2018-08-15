/*
 *This is a generic implementation of Thread pools 
 *using C++11
 *To use this ThreadPool, create
 *1) Create a ThreadPool object
 *2) Call the Init;
 *3) Assign a task to ThreadPool using AssignTask call
 */

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

class ThreadPool
{
public:
	ThreadPool();

	ThreadPool(unsigned nNumThreads);

private:
	unsigned m_nNumThreads;
	vector<std::thread> ThreadPool;
};

#endif
