#include "cGameField.h"
#include <random>
#include <ctime>
#include <SDL_timer.h>
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

void cGameField::generate()
{
	static bool b = false;
	if (!b)
	{
		srand(time(0));
		b = true;
	}
	int x = rand() % 590;
	int n = -(iLevel / 2) + rand() % iLevel;
	int iSpeed = iLevel / 2 + 1 + n;
	cMovingGraphObj meteorite("Textures/Meteorite.png", iSpeed, x, -100, x, 400);
	movingObjList.add(meteorite);
}

Uint32 gen(Uint32 interval, void* vParam)
{
	((cGameField*)vParam)->generate();
	return interval;
}

cGameField::cGameField(int iLevelInput):background("Textures/Background.jpg")
{
	if (iLevelInput <= 0)
		iLevelInput = 1;
	iLevel = iLevelInput;
	cGraphObj house("Textures/House.png");
	cGraphObj meteorite("Textures/Meteorite.png");
	int iPos = (640 - house.getRect().w - meteorite.getRect().w / 2) / (4 + iLevel);
	for (int i = 4 + iLevel; i >= 0; i--)
	{
		house.setPos(meteorite.getRect().w / 4 + i * iPos, 400);
		objList.add(house);
	}
}


cGameField::~cGameField()
{
}

cGameResult cGameField::start(SDL_Renderer* lpRenderer)
{
	SDL_TimerID generate_timer = SDL_AddTimer(2000, gen, this);
	int iScore = 0;

	SDL_Event event;
	SDL_Point click;

	bool bFlag = false;
	bool bPaused = false;
	while (!bFlag)
	{
		movingObjList.move();
		draw(lpRenderer);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				bFlag = true;
				bPaused = true;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					bFlag = true;
					bPaused = true;
				}
			}
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
			cTextObj loseMsg("a_AlternaSw.ttf", 40, "Игра окончена");
			loseMsg.setPos(320 - loseMsg.getRect().w / 2, 240 - loseMsg.getRect().h / 2);
			SDL_RemoveTimer(generate_timer);
			while (movingObjList.move())
			{
				draw(lpRenderer);
				loseMsg.paint(lpRenderer);
				SDL_RenderPresent(lpRenderer);
			}
			movingObjList.move();
			draw(lpRenderer);
			loseMsg.paint(lpRenderer);
			SDL_RenderPresent(lpRenderer);
			bFlag = true;
		}
	}
	SDL_RemoveTimer(generate_timer);
	return cGameResult(iScore, timer.getTime(), iLevel, bPaused);
}

void cGameField::draw(SDL_Renderer* lpRenderer)
{
	SDL_RenderClear(lpRenderer);
	background.paint(lpRenderer);
	objList.show(lpRenderer);
	movingObjList.show(lpRenderer);
	SDL_RenderPresent(lpRenderer);
}