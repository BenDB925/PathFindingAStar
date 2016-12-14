#include "ThreadPool.h"

ThreadedQueue * ThreadPool::_queue;
bool ThreadPool::_running;

ThreadPool::ThreadPool()
{
	_numThreads = SDL_GetCPUCount();
	_threads = new vector<SDL_Thread *>();
	_queue = new ThreadedQueue();
	_running = true;
	_initted = false;
	for (int i = 0; i < _numThreads; i++)
	{
		_threads->push_back(SDL_CreateThread(ThreadFunction, "thread" + i, this));
	}
}


ThreadPool::~ThreadPool()
{
}

void ThreadPool::addJob(Job * pJob)
{
	_queue->pushJob(pJob);
	_initted = true;
}

void ThreadPool::StopJobs()
{
	_running = false;

	std::vector<vector<Tile>> * map = new std::vector<vector<Tile>>();
	Job * dummyJob = new Job(Vector2i(0, 0), Vector2i(29, 29), map, 0);

	for (int i = 0; i < _threads->size(); i++)
		addJob(dummyJob);

	for (int i = 0; i < _threads->size(); i++)
	{
		if(SDL_GetThreadID(_threads->at(0)) != NULL)
			SDL_WaitThread(_threads->at(0), NULL);

		_threads->erase(_threads->begin());
	}

	delete dummyJob;
	delete map;
	delete _threads;
	delete _queue;
	
}

int ThreadPool::ThreadFunction(void * thisptr)
{
	ThreadPool* tp = (ThreadPool*)thisptr;
	tp->ProcessJobs();
	return 0;
}

void ThreadPool::ProcessJobs()
{
	while (_running)
	{
		Job * job = _queue->popJob();
		if(_running == true)
			job->execute();
	}
}
