#include "cGameResult.h"



cGameResult::cGameResult(int iScoreInput, unsigned uTimeInput, int iLevelInput, bool bPausedInput)
{
	iScore = iScoreInput;
	uTime = uTimeInput;
	iLevel = iLevelInput;
	bPaused = bPausedInput;
}


cGameResult::~cGameResult()
{
}

int cGameResult::getScore()
{
	return iScore;
}

unsigned cGameResult::getTime()
{
	return uTime;
}

int cGameResult::getLevel()
{
	return iLevel;
}

bool cGameResult::isPaused()
{
	return bPaused;
}