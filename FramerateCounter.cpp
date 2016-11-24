#include "FramerateCounter.h"
#include <iostream>


FramerateCounter::FramerateCounter()
{
	_countedFrames = 0;
	_fpsTimer = Timer();
	_fpsTimer.start();
	_timeInCurrSec = 0;
}


FramerateCounter::~FramerateCounter()
{
}

void FramerateCounter::update(SDL_Renderer * pRenderer)
{
	float dt = _fpsTimer.getTicks() / 1000.f;
	_timeInCurrSec += dt;
	++_countedFrames;

	if(_timeInCurrSec > 1)
	{
		_timeText = "";
		_timeText = "Average Frames Per Second " + std::to_string(_countedFrames);

		//std::cout << _timeText << std::endl;
		_countedFrames = 0;
		_timeInCurrSec = 0;
	}
}
