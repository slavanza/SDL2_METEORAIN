#pragma once

#include "cGame.h"
#include "cObjList.h"

class cGameField : public cGame
{
	cObjList objList;
	// доделать
public:
	cGameField();
	~cGameField();
};

