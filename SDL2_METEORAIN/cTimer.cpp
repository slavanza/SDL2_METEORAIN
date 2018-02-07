#include "cTimer.h"
#include <cstdio>
#include <cstring>


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

/** строка должна быть хотя бы 6 символов в длину */
char* cTimer::toStr(char* lpStr) 
{
	unsigned uMin, uSec;
	formatTime(getTime(), uMin, uSec);
	char szMin[3], szSec[3];
	sprintf_s(szMin, "%u", uMin);
	sprintf_s(szSec, "%u", uSec);
	if (strlen(szMin) == 1)
	{
		lpStr[0] = '0';
		lpStr[1] = szMin[0];
	}
	else
	{
		lpStr[0] = szMin[0];
		lpStr[1] = szMin[1];
	}
	lpStr[2] = ':';
	if (strlen(szSec) == 1)
	{
		lpStr[3] = '0';
		lpStr[4] = szSec[0];
	}
	else
	{
		lpStr[3] = szSec[0];
		lpStr[4] = szSec[1];
	}
	lpStr[5] = '\0';
	return lpStr;
}

void formatTime(Uint32 uMS, unsigned &uMin, unsigned &uSec)
{
	uMin = uMS / 60000;
	uSec = uMS / 1000 - uMin * 60;
}