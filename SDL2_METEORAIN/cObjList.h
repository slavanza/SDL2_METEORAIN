#pragma once
#include "cMovingGraphObj.h"


class cObjList
{
	struct cObjPage
	{
		cGraphObj data;
		cObjPage* lpNext;
		cObjPage(cGraphObj&);
	} *lpFront;
public:
	cObjList();
	~cObjList();
	void add(cGraphObj);
	void remove(int x);
	void show(SDL_Renderer*);
};

