#pragma once

#include <SDL.h>

class cTimer
{ 
	Uint32 uTicks;
public:
	cTimer();
	~cTimer();
	Uint32 getTime();
	Uint32 resetTime();
	char* toStr(char*);
};

void formatTime(Uint32, unsigned&, unsigned&);