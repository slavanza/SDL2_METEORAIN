#include "cRecordsMenu.h"
#include <cstdio>
#include <cstring>


char* toStr(char* lpStr, unsigned uTime)
{
	unsigned uMin, uSec;
	uMin = uTime / 60000;
	uSec = uTime / 1000 - uMin * 60;
	char szMin[3], szSec[3];
	sprintf_s(szMin, "%u", uMin);
	sprintf_s(szSec, "%u", uSec);
	for (int i = 0; i < 3; i++)
	{
		lpStr[i] = szMin[i];
		lpStr[i + 4] = szSec[i];
	}
	lpStr[3] = ':';
	lpStr[7] = '\0';
	return lpStr;
}


cRecordsMenu::cRecordsMenu() : cMenu(1, "Назад"), background("Textures/Menu.jpg"), title("a_AlternaSw.ttf", 40, "Records")
{
	title.setPos(320 - strlen(title.getText())* 25, 10);
	records.load("records.bin");
	for (int i = 0; i < 4; i++)
	{
		description[i].setSize(30);
		description[i].setFont("a_AlternaSw.ttf");
		description[i].setColor(238, 221, 130);
	}
	description[0].setText("Имя");
	description[0].setPos(80, 80);
	description[1].setText("Уровень");
	description[1].setPos(300, 80);
	description[2].setText("Время");
	description[2].setPos(400, 80);
	description[3].setText("Очки");
	description[3].setPos(500, 80);

	for (int i = 0; i < 10; i++)
	{
		names[i].setSize(30);
		names[i].setFont("a_AlternaSw.ttf");
		names[i].setText(records.get(i).getName());
		names[i].setPos(80, 240 + (i - 4) * 30);

		levels[i].setSize(30);
		levels[i].setFont("a_AlternaSw.ttf");
		char level[3] = "";
		sprintf_s(level, "%d", records.get(i).getMaxLevel());
		levels[i].setText(level);
		if(strlen(level) == 2)
			levels[i].setPos(330, 240 + (i - 4) * 30);
		else
			levels[i].setPos(300, 240 + (i - 4) * 30);

		times[i].setSize(30);
		times[i].setFont("a_AlternaSw.ttf");
		char time[10] = "";
		toStr(time, records.get(i).getTotalTime());
		times[i].setText(time);
		times[i].setPos(400, 240 + (i - 4) * 30);

		scores[i].setSize(30);
		scores[i].setFont("a_AlternaSw.ttf");
		char score[10] = "";
		sprintf_s(score, "%d", records.get(i).getTotalScore());
		scores[i].setText(score);
		scores[i].setPos(500, 240 + (i - 4) * 30);
	}
	lpArr->setPos(320 - strlen(lpArr->getText()) * 20, 420);
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
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_MOUSEMOTION:
			{
				SDL_Point move;
				move.x = event.motion.x;
				move.y = event.motion.y;
				int n = check(move);
				if (n)
				{
					lpArr->setColor(128, 128, 128);
				}
			}
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
