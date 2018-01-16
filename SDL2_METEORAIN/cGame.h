#pragma once

#include "cTimer.h"

class cGame
{
	int iScore; // очки
protected:
	cTimer timer; // таймер
	int incScore(int);
	int decScore(int);
public:
	cGame();
	~cGame();
	int getScore();
	Uint32 getTime();
};

