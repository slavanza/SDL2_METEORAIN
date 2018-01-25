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
		while (temp->lpNext)
		{
			if (SDL_HasIntersection(&rect, &(temp->data.getRect())))
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
			if (bMoving)
				iCount += 2;
			else
				iCount++;
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
		while (temp->lpNext)
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
		while (temp->lpNext)
		{
			temp->data.paint(lpRenderer);
			temp = temp->lpNext;
		}
	}
}

bool cMovingObjList::move() // ���������� ������� ����� ������ ������� ��� ������� � ���������, ����� �������� ����� ������� �������
{
	bool bMove = false;
	if (lpFront)
	{
		cMovingObjPage* temp = lpFront;
		while (temp->lpNext)
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