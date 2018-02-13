#include "cRecordsMenu.h"
#include <cstdio>
#include <cstring>
#include <iostream>


char* toStr(char* lpStr, unsigned uTime)
{
	unsigned uMin, uSec;
	uMin = uTime / 60000;
	uSec = uTime / 1000 - uMin * 60;
	char szMin[3], szSec[3];
	sprintf_s(szMin, "%u", uMin);
	sprintf_s(szSec, "%u", uSec);
	if (strlen(szMin) == 1)
	{
		lpStr[0] = '0';
		lpStr[1] = szMin[0];
	}
	else
	{
		lpStr[0] = szMin[0];
		lpStr[1] = szMin[1];
	}
	lpStr[2] = ':';
	if (strlen(szSec) == 1)
	{
		lpStr[3] = '0';
		lpStr[4] = szSec[0];
	}
	else
	{
		lpStr[3] = szSec[0];
		lpStr[4] = szSec[1];
	}
	lpStr[5] = '\0';
	return lpStr;
}


cRecordsMenu::cRecordsMenu() : cMenu(1, "Назад"), background("Textures/Menu.jpg")
{
	setTitle("Рекорды");
	records.load("records.bin");
	for (int i = 0; i < 4; i++)
	{
		description[i].setSize(35);
		description[i].setFont("a_AlternaSw.ttf");
		description[i].setColor(238, 221, 130);
	}
	description[0].setText("Имя");
	description[0].setPos(35, 80);
	description[1].setText("Уровень");
	description[1].setPos(260, 80);
	description[2].setText("Время");
	description[2].setPos(400, 80);
	description[3].setText("Очки");
	description[3].setPos(530, 80);

	for (int i = 0; i < 10; i++)
	{
		names[i].setSize(35);
		names[i].setFont("a_AlternaSw.ttf");
		names[i].setText(records.get(i).getName());
		names[i].setPos(35, 240 + (i - 4) * 32);

		levels[i].setSize(35);
		levels[i].setFont("a_AlternaSw.ttf");
		char level[3] = "";
		sprintf_s(level, "%d", records.get(i).getMaxLevel());
		levels[i].setText(level);
		levels[i].setPos(310 - levels[i].getRect().w / 2, 240 + (i - 4) * 32);

		times[i].setSize(35);
		times[i].setFont("a_AlternaSw.ttf");
		char time[10] = "";
		toStr(time, records.get(i).getTotalTime());
		times[i].setText(time);
		times[i].setPos(410, 240 + (i - 4) * 32);

		scores[i].setSize(35);
		scores[i].setFont("a_AlternaSw.ttf");
		char score[10] = "";
		sprintf_s(score, "%d", records.get(i).getTotalScore());
		scores[i].setText(score);
		scores[i].setPos(565 - scores[i].getRect().w / 2, 240 + (i - 4) * 32);
	}
	lpArr->setPos(320 - lpArr->getRect().w / 2, 430);
}


cRecordsMenu::~cRecordsMenu()
{
}

void cRecordsMenu::draw(SDL_Renderer* lpRenderer)
{
	SDL_RenderClear(lpRenderer);
	background.paint(lpRenderer);
	title.paint(lpRenderer);
	for (int i = 0; i < 4; i++)
	{
		description[i].paint(lpRenderer);
	}
	for (int i = 0; i < 10; i++)
	{
		names[i].paint(lpRenderer);
		levels[i].paint(lpRenderer);
		times[i].paint(lpRenderer);
		scores[i].paint(lpRenderer);
	}
	lpArr->paint(lpRenderer);
	SDL_RenderPresent(lpRenderer);
}

void cRecordsMenu::choose(SDL_Renderer* lpRenderer)
{
	bool bFlag = false;

	SDL_Event event;

	while (!bFlag)
	{
		draw(lpRenderer);
		SDL_Point cur;
		SDL_GetMouseState(&cur.x, &cur.y);
		int n = check(cur);
		if (n)
		{
			lpArr->setColor();	
		}			
		else
		{
			lpArr->setColor(128, 128, 128);
		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					SDL_Point click;
					click.x = event.button.x;
					click.y = event.button.y;
					if (check(click) != -1)
						bFlag = true;
				}
			}
		}
	}
}
