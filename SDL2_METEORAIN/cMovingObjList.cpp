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

int cMovingObjList::remove(SDL_Rect rect)
{
	int iCount = 0;
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp)
		{
			bool bMoving = false;
			if (SDL_HasIntersection(&rect, &(temp->data.getRect())))
			{
				bMoving = temp->data.isMoving();
				if (bMoving)
					iCount += 2;
				else
					iCount++;
				if (temp != lpFront)
				{
					cMovingObjPage* _temp = lpFront;
					while (_temp->lpNext != temp)
					{
						_temp = _temp->lpNext;
					}
					cMovingObjPage* buf = temp->lpNext;
					delete temp;
					_temp->lpNext = buf;
				}
				else
				{
					lpFront = lpFront->lpNext;
					delete temp;
					temp->lpNext = lpFront;
				}
			}
			temp = temp->lpNext;
		}
	}
	return iCount;
}

int cMovingObjList::remove(SDL_Point point)
{
	int iCount = 0;
	cMovingObjPage *temp = lpFront;
	while (temp)
	{
		bool bMoving = false;
		if (SDL_EnclosePoints(&point, 1, &(temp->data.getRect()), NULL))
		{
			bMoving = temp->data.isMoving();
			if (bMoving)
				iCount += 2;
			else
				iCount++;
			cMovingObjPage *_temp = lpFront;
			if (_temp == temp)
			{
				lpFront = lpFront->lpNext;
				delete temp;
				temp->lpNext = lpFront;
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
		}
		temp = temp->lpNext;
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
		iCount++;
	}
	return &(cur->data);
}

int cMovingObjList::find(SDL_Rect rect)
{
	int iCount = 0;
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
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

void cMovingObjList::show(SDL_Renderer* lpRenderer)
{
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp)
		{
			temp->data.paint(lpRenderer);
			temp = temp->lpNext;
		}
	}
}

bool cMovingObjList::move() // необходимо сделать чтобы таймер вызывал эту функцию с перерывом, иначе движение будет слишком быстрым
{
	bool bMove = false;
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp)
		{
			if (!(temp->data.move()))
				temp->data.changeImg("Textures/Fallen.png");
			else
				bMove = true;
			temp = temp->lpNext;
		}
	}
	return bMove;
}

bool cMovingObjList::isEmpty()
{
	return lpFront == nullptr;
}

int cMovingObjList::getLen()
{
	if (lpFront == nullptr)
		return 0;
	int iCount = 0;
	cMovingObjPage* temp = lpFront;
	while(temp)
	{
		iCount++;
		temp = temp->lpNext;
	}
	return iCount;
}