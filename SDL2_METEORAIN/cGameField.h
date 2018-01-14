#pragma once

#include "cGame.h"
#include "cObjList.h"
#include "cMovingObjList.h"

class cGameField : public cGame
{
	cObjList objList;
	cMovingObjList movingObjList;
	cGraphObj background;
	int iLevel;
	// доделать
	void compare();
public:
	cGameField(int);
	~cGameField();
};

