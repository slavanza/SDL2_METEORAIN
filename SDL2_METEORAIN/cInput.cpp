#include "cInput.h"
#include <cstring>
#include <iostream>


cInput::cInput():background("Textures/Menu.jpg"), title("a_AlternaSw.ttf", 40, "")
{
	for (int i = 0; i < 21; i++)
		szBuf[i] = '\0';
}

cInput::cInput(char* szTitle):background("Textures/Menu.jpg"), title("a_AlternaSw.ttf", 40, szTitle)
{
	title.setPos(320 - title.getRect().w / 2, 80 - title.getRect().h / 2);
	for (int i = 0; i < 21; i++)
		szBuf[i] = '\0';
}

cInput::~cInput()
{
}

void cInput::setTitle(char* szTitle)
{
	title.setText(szTitle);
	title.setPos(320 - title.getRect().w / 2, 80 - title.getRect().h / 2);
}

char* cInput::input(SDL_Renderer* lpRenderer)
{
	bool bFlag = false;
	SDL_Event event;
	int iCur = 0, iLastLen = 0;
	SDL_StartTextInput();
	while (!bFlag)
	{
		draw(lpRenderer);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				SDL_StopTextInput();
				exit(1);
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					strcpy_s(szBuf, "no_name");
					bFlag = true;
				}
				if (event.key.keysym.sym == SDLK_BACKSPACE)
					if (iCur != 0)
					{
						iCur-=iLastLen;
						szBuf[iCur] = '\0';
					}
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					if ((!strcmp(szBuf, "")) || (!strcmp(szBuf, "\n")))
						strcpy_s(szBuf, "no_name");
					bFlag = true;
				}
				break;
			case SDL_TEXTINPUT:
				if (iCur < 20)
				{
					if (!strcat_s(szBuf, event.text.text))
					{
						iLastLen = strlen(event.text.text);
						iCur += iLastLen;
					}
					if (iCur > 20)
						iCur = 20;
				}
				break;
			}
		}
	}
	SDL_StopTextInput();
	return szBuf;
}

void cInput::draw(SDL_Renderer* lpRenderer)
{
	cTextObj text("a_AlternaSw.ttf", 35, szBuf);
	text.setPos(320 - text.getRect().w / 2, 240 - text.getRect().h / 2);
	background.paint(lpRenderer);
	title.paint(lpRenderer);
	text.paint(lpRenderer);
	SDL_RenderPresent(lpRenderer);
}