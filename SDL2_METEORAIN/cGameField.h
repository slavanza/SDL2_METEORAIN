#pragma once

#include "cGame.h"
#include "cObjList.h"
#include "cMovingObjList.h"
#include "cGameResult.h"

class cGameField : public cGame
{
	cObjList objList;
	cMovingObjList movingObjList;
	cGraphObj background;
	int iLevel;
	// доделать
	int compare();
public:
	cGameField(int);
	~cGameField();
	cGameResult start(); // на вход скорее всего будет приниматься структура 'игрок'
	void draw(SDL_Renderer*);
};

