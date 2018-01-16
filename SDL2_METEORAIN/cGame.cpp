#include "cGame.h"



int cGame::incScore(int iInc)
{
	iScore += iInc;
	return iScore;
}

int cGame::decScore(int iDec)
{
	iScore -= iDec;
	return iScore;
}

cGame::cGame()
{
	iScore = 0;
}


cGame::~cGame()
{
}

int cGame::getScore()
{
	return iScore;
}

Uint32 cGame::getTime()
{
	return timer.getTime();
}