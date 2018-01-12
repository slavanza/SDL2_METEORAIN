#include "cObjList.h"



cObjList::cObjList()
{
	lpFront = nullptr;
}


cObjList::~cObjList()
{
}

void cObjList::add(cGraphObj input)
{
	if (lpFront)
	{
		cObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			// доделать
		}
	}
}