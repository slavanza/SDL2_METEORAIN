#pragma once

#include "cTimer.h"

class cGame
{
	int iScore; // очки
	int iHealth; // уровень здоровья
	int iDamage; // количество урона
private:
	cTimer timer; // таймер
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

