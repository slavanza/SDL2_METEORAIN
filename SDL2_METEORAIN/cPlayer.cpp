#include "cPlayer.h"
#include <cstring>


cPlayer::cPlayer()
{
	strcpy_s(szName, "no_name");
	uMaxLevel = uTotalScore = uTotalTime = 0;
}

cPlayer::cPlayer(char* szNameInput)
{
	strcpy_s(szName, szNameInput);
	uMaxLevel = uTotalScore = uTotalTime = 0;
}

cPlayer::~cPlayer()
{
}

unsigned cPlayer::incTotalScore(unsigned uInc)
{
	uTotalScore += uInc;
	return uTotalScore;
}

unsigned cPlayer::incMaxLevel(unsigned uInc)
{
	uMaxLevel += uInc;
	return uMaxLevel;
}

unsigned cPlayer::incTotalTime(unsigned uInc)
{
	uTotalTime += uInc / 1000;
	return uTotalTime;
}

char* cPlayer::getName()
{
	return szName;
}

unsigned cPlayer::getMaxLevel()
{
	return uMaxLevel;
}

unsigned cPlayer::getTotalScore()
{
	return uTotalScore;
}

unsigned cPlayer::getTotalTime()
{
	return uTotalTime;
}

const cPlayer& cPlayer::updateFromResult(cGameResult& input)
{
	unsigned uResultScore = input.getScore();
	unsigned uLevel = input.getLevel();
	unsigned uTime = input.getTime();
	uTotalScore += uResultScore;
	if (uMaxLevel < uLevel)
	{
		uMaxLevel = uLevel;
	}
	uTotalTime += uTime;
	return *this;
}