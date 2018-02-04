#include "cTimer.h"
#include <cstdio>


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

/** строка должна быть хотя бы 8 символов в длину */
char* cTimer::toStr(char* lpStr) 
{
	unsigned uMin, uSec;
	formatTime(getTime(), uMin, uSec);
	char szMin[3], szSec[3];
	sprintf_s(szMin, "%u", uMin);
	sprintf_s(szSec, "%u", uSec);
	for (int i = 0; i < 3; i++)
	{
		lpStr[i] = szMin[i];
		lpStr[i + 4] = szSec[i];
	}
	lpStr[3] = ':';
	lpStr[7] = '\0';
	return lpStr;
}

void formatTime(Uint32 uMS, unsigned &uMin, unsigned &uSec)
{
	uMin = uMS / 60000;
	uSec = uMS / 1000 - uMin * 60;
}