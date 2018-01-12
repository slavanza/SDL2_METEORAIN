#include "cObjList.h"



cObjList::cObjPage::cObjPage(cGraphObj& input):data(input)
{
	lpNext = nullptr;
}

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
			temp = temp->lpNext;
		}
		temp->lpNext = new cObjPage(input);
	}
	else
		lpFront = new cObjPage(input);
}

void cObjList::remove(int x)
{
	if (lpFront)
	{
		cObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			if ((temp->data.getRect().x < x) && ((temp->data.getRect().x + temp->data.getRect().w) > x))
			{
				cObjPage* _temp = lpFront;
				while (_temp->lpNext != temp)
				{
					_temp = _temp->lpNext;
				}
				cObjPage* buf = temp->lpNext;
				delete temp;
				_temp->lpNext = buf;
			}
			temp = temp->lpNext;
		}
	}
}

void cObjList::show(SDL_Renderer* lpRenderer)
{
	if (lpFront)
	{
		cObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			temp->data.paint(lpRenderer);
			temp = temp->lpNext;
		}
	}
}