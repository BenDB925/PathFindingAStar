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
	queue<Job*> _jobQueue;

private:
	SDL_mutex* _lock;
	SDL_cond* _available;
};

