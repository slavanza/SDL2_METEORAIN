#include "cGameField.h"

int cGameField::compare()
{
	cMovingGraphObj* lpCur = movingObjList.get(0);
	int iCur = 0;
	int iCount = 0;
	while (lpCur)
	{
		SDL_Rect rect = lpCur->getRect();
		if (objList.find(rect))
		{
			iCount += objList.remove(rect);
		}
		lpCur = movingObjList.get(++iCur);
	}
	return iCount;
}

cGameField::cGameField(int iLevelInput):background("default")
{
	iLevel = iLevelInput;
	switch (iLevel)
	{
	case 0:
	{
		cGraphObj temp("level_0");
		background = temp;
	}
		break;
	case 1:
	{
		cGraphObj temp("level_1");
		background = temp;
	}
		break;
	default:
		;
	}
}


cGameField::~cGameField()
{
}

int cGameField::start()
{
	return 0;
}