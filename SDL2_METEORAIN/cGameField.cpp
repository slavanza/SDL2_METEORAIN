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

cGameResult cGameField::start()
{
	int iScore = 0;

	SDL_Event event;
	SDL_Point click;

	bool bFlag = false;
	while (!bFlag)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					click.x = event.button.x;
					click.y = event.button.y;
					incScore(movingObjList.remove(click));
				}
			}
		}
		int iDestroyed = compare();
		if (iDestroyed)
		{
			decScore(iDestroyed);
		}
		if (objList.isEmpty())
		{
			bFlag = true;
		}
	}
	return cGameResult(iScore, timer.getTime(), iLevel);
}

void cGameField::draw(SDL_Renderer* lpRenderer)
{
	background.paint(lpRenderer);
	objList.show(lpRenderer);
	movingObjList.show(lpRenderer);
}