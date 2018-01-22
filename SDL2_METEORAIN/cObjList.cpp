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

int cObjList::remove(SDL_Rect rect)
{
	int iCount = 0;
	cObjPage *temp = lpFront;
	while (temp)
	{
		if (SDL_HasIntersection(&rect, &(temp->data.getRect())))
		{
			cObjPage *_temp = lpFront;
			if (_temp == temp)
			{
				if (temp->lpNext == nullptr)
				{
					delete temp;
					temp = lpFront = nullptr;
				}
				else
				{
					lpFront = lpFront->lpNext;
					delete temp;
					temp->lpNext = lpFront;
				}
			}
			else
			{
				while (_temp->lpNext != temp)
				{
					_temp = _temp->lpNext;
				}
				_temp->lpNext = temp->lpNext;
				delete temp;
				temp = _temp;
			}
			iCount++;
		}
		if(temp)
			temp = temp->lpNext;
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
		iCount++;
	}
	return &(cur->data);
}

int cObjList::find(SDL_Rect rect)
{
	int iCount = 0;
	if (lpFront)
	{
		cObjPage* temp = lpFront;
		while (temp)
		{
			if (SDL_HasIntersection(&rect, &(temp->data.getRect())))
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
		while (temp)
		{
			temp->data.paint(lpRenderer);
			temp = temp->lpNext;
		}
	}
}

bool cObjList::isEmpty()
{
	return (lpFront == nullptr);
}