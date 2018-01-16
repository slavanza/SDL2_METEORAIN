#pragma once
#include "cGraphObj.h"

class cObjList
{
private:
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
	int remove(SDL_Rect);
	cGraphObj* get(int);
	int find(SDL_Rect);
	void show(SDL_Renderer*);
	bool isEmpty();
};

