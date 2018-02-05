#pragma once

#include "cGame.h"
#include "cObjList.h"
#include "cMovingObjList.h"
#include "cGameResult.h"
#include "cTextObj.h"

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
	cGameResult start(SDL_Renderer*);
	void draw(SDL_Renderer*);
	friend Uint32 gen(Uint32, void*);
};

