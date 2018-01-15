#include "cGameResult.h"



cGameResult::cGameResult(int iScoreInput, unsigned uTimeInput, int iLevelInput)
{
	iScore = iScoreInput;
	uTime = uTimeInput;
	iLevel = iLevelInput;
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