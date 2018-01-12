#pragma once

#include <SDL_timer.h>

class cTimer
{ 
	Uint32 uTicks;
public:
	cTimer();
	~cTimer();
	Uint32 getTime();
	Uint32 resetTime();
};

