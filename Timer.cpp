#include "Timer.h"
#include <SDL.h>


Timer::Timer()
{
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mLastTicks = mStartTicks;
}

Timer::~Timer()
{
}

void Timer::start()
{
	mStartTicks = SDL_GetTicks();
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 timeSinceStart = 0;

	timeSinceStart = SDL_GetTicks() - mStartTicks;
	mLastTicks = mCurrTime;
	mCurrTime = timeSinceStart;
	Uint32 diff = mCurrTime - mLastTicks;

	return diff;
}