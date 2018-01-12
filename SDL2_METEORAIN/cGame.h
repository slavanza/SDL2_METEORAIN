#pragma once

#include "cTimer.h"

class cGame
{
	int iScore;
	int iHealth;
	int iDamage;
private:
	cTimer timer;
public:
	cGame();
	~cGame();
	int getScore();
	int getHealth();
	int getDamage();
	bool heal();
	bool dealDamage(int);
	Uint32 getTime();
};

