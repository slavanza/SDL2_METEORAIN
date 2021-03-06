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
	int remove(SDL_Rect);
	int remove(SDL_Point);
	cMovingGraphObj* get(int);
	int find(SDL_Rect);
	void show(SDL_Renderer*);
	bool move();
	bool isEmpty();
	int getLen();
};

