#pragma once
#include <queue>
#include "Job.h"
using namespace std;

class ThreadedQueue
{
public:
	ThreadedQueue();
	~ThreadedQueue();

	void pushJob(Job * pJob);
	Job * popJob();

private:
	queue<Job*> _jobQueue;
	SDL_mutex* _lock;
	SDL_cond* _available;
};

