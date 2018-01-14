#include "cMovingObjList.h"

cMovingObjList::cMovingObjPage::cMovingObjPage(cMovingGraphObj& input):data(input)
{
	lpNext = nullptr;
}

cMovingObjList::cMovingObjList()
{
	lpFront = nullptr;
}


cMovingObjList::~cMovingObjList()
{
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (lpFront)
		{
			temp = lpFront;
			lpFront = lpFront->lpNext;
			delete temp;
		}
	}
}

void cMovingObjList::add(cMovingGraphObj input)
{
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			temp = temp->lpNext;
		}
		temp->lpNext = new cMovingObjPage(input);
	}
	else
		lpFront = new cMovingObjPage(input);
}

int cMovingObjList::remove(int x, int y)
{
	int iCount = 0;
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			if ((temp->data.getRect().x < x) && ((temp->data.getRect().x + temp->data.getRect().w) > x) && (temp->data.getRect().y < y) && ((temp->data.getRect().y + temp->data.getRect().h) > y))
			{
				cMovingObjPage* _temp = lpFront;
				while (_temp->lpNext != temp)
				{
					_temp = _temp->lpNext;
				}
				cMovingObjPage* buf = temp->lpNext;
				delete temp;
				_temp->lpNext = buf;
				iCount++;
			}
			temp = temp->lpNext;
		}
	}
	return iCount;
}

cMovingGraphObj* cMovingObjList::get(int n)
{
	if (!lpFront)
		return nullptr;
	int iCount = 0;
	cMovingObjPage* cur = lpFront;
	while (iCount < n)
	{
		cur = cur->lpNext;
		if (cur == nullptr)
			return nullptr;
	}
	return &(cur->data);
}

void cMovingObjList::show(SDL_Renderer* lpRenderer)
{
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			temp->data.paint(lpRenderer);
			temp = temp->lpNext;
		}
	}
}

void cMovingObjList::move()
{
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp->lpNext)
		{
			temp->data.move();
			temp = temp->lpNext;
		}
	}
}