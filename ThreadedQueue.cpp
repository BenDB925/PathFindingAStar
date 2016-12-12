#include "ThreadedQueue.h"



ThreadedQueue::ThreadedQueue()
{
	_lock = SDL_CreateMutex();
	_available = SDL_CreateCond();
}


ThreadedQueue::~ThreadedQueue()
{
}

void ThreadedQueue::pushJob(Job * pJob)
{
	SDL_LockMutex(_lock);
	_jobQueue.push(pJob);
	SDL_CondBroadcast(_available);
	SDL_UnlockMutex(_lock);
}

Job * ThreadedQueue::popJob()
{
	SDL_LockMutex(_lock);

	while(_jobQueue.empty())
		SDL_CondWait(_available, _lock);

	Job * job = _jobQueue.front();
	_jobQueue.pop();
	SDL_UnlockMutex(_lock);
	return job;
}
