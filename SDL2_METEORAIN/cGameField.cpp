#include "cGameField.h"
#include <random>
#include <ctime>
#include <SDL_timer.h>
#include <iostream>
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
	int x;
	if(objList.getLen() > 3)
		x = rand() % 590;
	else
	{
		int n = rand() % objList.getLen();
		x = objList.get(n)->getRect().x + rand() % 80 - 40;
	}
	int iSpeed = 1 + rand() % (iLevel + 1) / 2;
	cMovingGraphObj meteorite("Textures/Meteorite.png", iSpeed, x, -100, x, 400);
	movingObjList.add(meteorite);
}

Uint32 gen(Uint32 interval, void* vParam)
{
	static unsigned time = 0;
	static int iL = -1;
	if(time == 0)
		time = ((cGameField*)vParam)->getTime();
	((cGameField*)vParam)->generate();
	if (interval > 1000)
	{
		if ((time - ((cGameField*)vParam)->getTime()) % 1000 >= 10)
		{
			++iL %= 2;
			if(!iL)
				((cGameField*)vParam)->iLevel++;
			interval -= 250;
			time = ((cGameField*)vParam)->getTime();
		}

	}
	return interval;
}

int cGameField::incScore(int iInc)
{
	iScore += iInc;
	return iScore;
}

int cGameField::decScore(int iDec)
{
	iScore -= iDec;
	if (iScore < 0)
		iScore = 0;
	return iScore;
}

cGameField::cGameField(int iLevelInput):background("Textures/Background.jpg")
{
	if (iLevelInput < 0)
		iLevelInput = 0;
	iLevel = iLevelInput;
	cGraphObj house("Textures/House.png");
	cGraphObj meteorite("Textures/Meteorite.png");
	int iPos = (640 - house.getRect().w) / (5 + iLevel);
	for (int i = 0; i < (5 + iLevel); i++)
	{
		house.setPos(iPos / 2 + i * iPos, 400);
		objList.add(house);
	}
}


cGameField::~cGameField()
{
}

int cGameField::getScore()
{
	return iScore;
}

Uint32 cGameField::getTime()
{
	return timer.getTime();
}

cGameResult cGameField::start(SDL_Renderer* lpRenderer)
{
	SDL_TimerID generate_timer = SDL_AddTimer(4000, gen, this);

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
		compare(); // уничтожение
		if (objList.isEmpty())
		{
			cTextObj loseMsg("a_AlternaSw.ttf", 40, "Игра окончена");
			loseMsg.setPos(320 - loseMsg.getRect().w / 2, 240 - loseMsg.getRect().h / 2);
			cTextObj tip("a_AlternaSw.ttf", 30, "Для выхода нажмите любую клавишу");
			tip.setPos(320 - tip.getRect().w / 2, 460 - tip.getRect().h);
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
			SDL_Event event;
			while (!bFlag)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						bFlag = true;
					}
					if (event.type == SDL_KEYDOWN)
					{
						bFlag = true;
					}
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						bFlag = true;
					}
				}
			}
		}
	}
	SDL_RemoveTimer(generate_timer);
	std::cout << "Total time: " << timer.getTime() << std::endl;
	return cGameResult(getScore(), timer.getTime(), iLevel, bPaused);
}

void cGameField::draw(SDL_Renderer* lpRenderer)
{
	SDL_RenderClear(lpRenderer);
	background.paint(lpRenderer);
	objList.show(lpRenderer);
	movingObjList.show(lpRenderer);

	char szTime[6];
	char szScore[7];
	_itoa_s(iScore, szScore, 10);
	szScore[6] = '\0';
	int iLen = strlen(szScore);
	for (int j = 0; j < (6 - iLen); j++)
	{
			for (int i = 5; i > 0; i--)	
				szScore[i] = szScore[i - 1];
		szScore[j] = '0';
	}
	cTextObj score("a_AlternaSw.ttf", 40, szScore);
	cTextObj time("a_AlternaSw.ttf", 45, timer.toStr(szTime));
	score.setColor(238, 221, 130);
	time.setColor(255, 64, 64);
	score.setPos(320 - score.getRect().w / 2, 15 + time.getRect().h);
	time.setPos(320 - time.getRect().w / 2, 10);
	score.paint(lpRenderer);
	time.paint(lpRenderer);

	SDL_RenderPresent(lpRenderer);
}