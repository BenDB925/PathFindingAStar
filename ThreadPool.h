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
	bool _initted = false;

private:
	static int ThreadFunction(void * thisptr);
	void ProcessJobs();
	vector<SDL_Thread *> * _threads;
	static bool _running;
	int _numThreads;
};

