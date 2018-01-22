#pragma once

#include "cGame.h"
#include "cObjList.h"
#include "cMovingObjList.h"
#include "cGameResult.h"
//#include "cPlayer.h"

class cGameField : public cGame
{
	cObjList objList;
	cMovingObjList movingObjList;
	cGraphObj background;
	int iLevel;
	int compare();
	void generate();
public:
	cGameField(int);
	~cGameField();
	cGameResult start(SDL_Renderer*); // на вход скорее всего будет приниматься структура 'игрок'; SDL_Renderer - временный параметр
	void draw(SDL_Renderer*);
	friend Uint32 gen(Uint32, void*);
};

