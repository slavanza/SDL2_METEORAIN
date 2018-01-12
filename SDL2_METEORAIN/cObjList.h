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
	void remove(/* входным параметром будет некоторое данное, при совпадении с одним из полей, объект будет удаляться из списка */);
	void show(SDL_Renderer*);
};

