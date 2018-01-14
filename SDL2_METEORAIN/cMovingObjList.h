#pragma once

#include "cMovingGraphObj.h"

class cMovingObjList
{
private:
	struct cMovingObjPage
	{
		cMovingGraphObj data;
		cMovingObjPage* lpNext;
		cMovingObjPage(cMovingGraphObj&);
	} *lpFront;
public:
	cMovingObjList();
	~cMovingObjList();
	void add(cMovingGraphObj);
	int remove(int, int);
	cMovingGraphObj* get(int);
	void show(SDL_Renderer*);
	void move();
};

