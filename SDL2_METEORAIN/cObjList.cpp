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
	if (lpFront)
	{
		cObjPage* temp = lpFront;
		while (lpFront)
		{
			temp = lpFront;
			lpFront = lpFront->lpNext;
			delete temp;
		}
	}
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

int cObjList::remove(int x)
{
	int iCount = 0;
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
				iCount++;
			}
			temp = temp->lpNext;
		}
	}
	return iCount;
}

cGraphObj* cObjList::get(int n)
{
	if (!lpFront)
		return nullptr;
	int iCount = 0;
	cObjPage* cur = lpFront;
	while (iCount < n)
	{
		cur = cur->lpNext;
		if (cur == nullptr)
			return nullptr;
	}
	return &(cur->data);
}

int cObjList::find(int x)
{
	int iCount = 0;
	if (lpFront)
	{
		cObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			if ((temp->data.getRect().x < x) && ((temp->data.getRect().x + temp->data.getRect().w) > x))
			{
				iCount++;
			}
			temp = temp->lpNext;
		}
	}
	return iCount;
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