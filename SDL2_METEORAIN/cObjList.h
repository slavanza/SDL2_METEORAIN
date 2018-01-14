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
	int remove(int);
	cGraphObj* get(int);
	int find(int);
	void show(SDL_Renderer*);
};

