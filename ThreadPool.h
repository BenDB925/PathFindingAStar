#pragma once
#include <vector>
#include <SDL.h>
#include "ThreadedQueue.h"

using namespace std;

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void addJob(Job * pJob);
	void StopJobs();
	static ThreadedQueue *_queue;

private:
	static int ThreadFunction(void * thisptr);
	void ProcessJobs();
	vector<SDL_Thread *> _threads;
	bool _initted = false;
	int _numThreads;
};

