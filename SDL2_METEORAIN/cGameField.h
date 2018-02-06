#pragma once

#include "cTimer.h"
#include "cObjList.h"
#include "cMovingObjList.h"
#include "cGameResult.h"
#include "cTextObj.h"

class cGameField
{
	int iScore;
	cTimer timer;
	cObjList objList;
	cMovingObjList movingObjList;
	cGraphObj background;
	int iLevel;
	int compare();
	void generate();
protected:
	int incScore(int);
	int decScore(int);
public:
	cGameField(int);
	~cGameField();
	int getScore();
	Uint32 getTime();
	cGameResult start(SDL_Renderer*);
	void draw(SDL_Renderer*);
	friend Uint32 gen(Uint32, void*);
};

