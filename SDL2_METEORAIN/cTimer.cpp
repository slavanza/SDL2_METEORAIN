#include "cTimer.h"



cTimer::cTimer()
{
	uTicks = SDL_GetTicks();
}


cTimer::~cTimer()
{
}

Uint32 cTimer::getTime()
{
	return SDL_GetTicks() - uTicks;
}

Uint32 cTimer::resetTime()
{
	Uint32 uTime = SDL_GetTicks() - uTicks;
	uTicks = uTime + uTicks;
	return uTime;
}

void formatTime(Uint32 uMS, unsigned &uMin, unsigned &uSec)
{
	uMin = uMS / 60000;
	uSec = uMS / 1000 - uMin * 60;
}