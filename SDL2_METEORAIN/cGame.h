#pragma once

#include "cTimer.h"

class cGame
{
	int iScore; // ����
protected:
	cTimer timer; // ������
	int incScore(int);
	int decScore(int);
public:
	cGame();
	~cGame();
	int getScore();
	Uint32 getTime();
};

