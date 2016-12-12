#include "ThreadPool.h"

ThreadedQueue * ThreadPool::_queue;

ThreadPool::ThreadPool()
{
	_numThreads = SDL_GetCPUCount();
	_threads = vector<SDL_Thread *>();
	_queue = new ThreadedQueue();

	for (int i = 0; i < _numThreads; i++)
	{
		SDL_CreateThread(ThreadFunction, "thread" + i, this);
	}
}


ThreadPool::~ThreadPool()
{
}

void ThreadPool::addJob(Job * pJob)
{
	_queue->pushJob(pJob);
}

void ThreadPool::StopJobs()
{
	
}

int ThreadPool::ThreadFunction(void * thisptr)
{
	ThreadPool* tp = (ThreadPool*)thisptr;
	tp->ProcessJobs();
	return 0;
}

void ThreadPool::ProcessJobs()
{
	while (true)
	{
		Job * job = _queue->popJob();
		job->execute();
	}
}
