#pragma once

#include "cGameResult.h"

class cPlayer
{
	char szName[21];
	unsigned uMaxLevel;
	unsigned uTotalScore;
	unsigned uTotalTime;
public:
	cPlayer();
	cPlayer(char*);
	~cPlayer();
	unsigned incTotalScore(unsigned);
	unsigned incMaxLevel(unsigned = 1);
	unsigned incTotalTime(unsigned);
	char* getName();
	unsigned getMaxLevel();
	unsigned getTotalScore();
	unsigned getTotalTime();
	const cPlayer& updateFromResult(cGameResult&);
};

