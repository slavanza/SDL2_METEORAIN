#pragma once
#include "cMovingGraphObj.h"


class cObjList
{
	struct cObjPage
	{
		cGraphObj data;
		cObjPage* lpNext;
	} *lpFront;
public:
	cObjList();
	~cObjList();
	void add(cGraphObj);
};

