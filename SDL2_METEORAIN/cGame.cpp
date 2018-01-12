#include "cGame.h"



cGame::cGame()
{
	iScore = 0;
	iDamage = 0;
	iHealth = 100;
}


cGame::~cGame()
{
}

int cGame::getScore()
{
	return iScore;
}

int cGame::getDamage()
{
	return iDamage;
}

int cGame::getHealth()
{
	return iHealth;
}

bool cGame::heal()
{
	iHealth += iHealth / 100;
	if (iDamage > (iHealth / 100))
		iDamage -= iHealth / 100;
	else
	{
		iDamage = 0;
		return false;
	}
	return true;
}

bool cGame::dealDamage(int iDamageIncome)
{
	iDamage += iDamageIncome;
	if (iHealth > iDamage)
		return true;
	else
		return false;
}

Uint32 cGame::getTime()
{
	return timer.getTime();
}