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
	if (iHealth < 100)
		iHealth += iHealth / 100;
	else
		return false;
	return true;
}

bool cGame::dealDamage(int iDamageIncome)
{
	iDamage += iDamageIncome;
	iHealth -= iDamageIncome;
	if (iHealth > 0)
		return true;
	else
		return false;
}

Uint32 cGame::getTime()
{
	return timer.getTime();
}