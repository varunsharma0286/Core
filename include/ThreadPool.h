/*
 *This is a generic implementation of Thread pools 
 *using C++11
 *To use this ThreadPool, create
 *1) Create a ThreadPool object
 *2) Call the Init from the main thread;
 *3) Assign a task to ThreadPool using AssignTask call
 */

#include<thread>
#include <mutex>
#include <condition_variable>
#include<iostream>



#ifndef _THREADPOOL_H
#define _THREADPOOL_H

//This Thread will be used by "ThreadPool"
struct Thread
{
public:
	Thread() = delete;
	Thread(const Thread&) = delete;
	void operator = (const Thread&) = delete;

	Thread(unsigned nId):
	m_Thread(),
	m_nThradId(nId),
	m_bStopThread(false)
	{
	}
	
	std::thread m_Thread;
	std::queue<string> m_Queue;
	void Assign(string sLog)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		mQueue.push(sLog);
		m_ConditionVar.notify_one();
	}

	void StartThread()
	{
		m_Thread = std::thread(&Thread::ThreadFunction,this);
	}

	void StopThread()
	{
		//Check if already stopped
		if(m_bStopThread)
		{
			return;
		}

		std::unique_lock<std::mutex> lock(m_Mutex);
		m_bStopThread = true;
		m_ConditionVar.notify_one();
		m_Thread.join();
	}

	void ThreadFunction();
	{
		while(not m_bStopThread)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			while(not m_Queue.empty())
			{
				std::cout<<m_nThreadId<<":"<<m_Queue.front()<<std::endl;
				m_Queue.pop();
			}
			m_ConditionVar.wait(lock);
			
			//This wait takes a predicate that is used to loop until it returns false; this overload may be used to avoid spurious wakeups.
			/*m_ConditionVar.wait(lock, [&](){return !m_Queue.empty();});
			while(not m_Queue.empty())
			{
				std::cout<<m_nThreadId<<":"<<m_Queue.front()<<std::endl;
				m_Queue.pop();
			}*/
		}

		//Finish up the leftover	
		std::unique_lock<std::mutex> lock(m_Mutex);
		while(not m_Queue.empty())
		{
			std::cout<<m_nThreadId<<":"<<m_Queue.front()<<std::endl;
			m_Queue.pop();
		}
	
		std::cout<<"Exiting thread:"<<m_nThreadId<<std::endl;
	}

	~Thread()
	{
		StopThread();
	}

private:
	std::mutex m_Mutex;
	std::condition_variable m_ConditionVar;
	const unsigned m_nThreadId;
	bool m_bStopThread;
}

class ThreadPool
{
public:
	ThreadPool();

	ThreadPool(unsigned nNumThreads);

	bool Init();

	void Stop();

	void AssignTask();
	//void ResizeThreadPool(unsigned nNumThreads)
	
private:
	unsigned m_nNumThreads;
	vector<Thread> m_ThreadPool; 
	bool m_bIsInitialized;
	atomic<unsigned> m_nThreadIndex = 0; //Initialized to point to first thread;
};

#endif
