#include "cMenu.h"
#include <cstring>


int cMenu::check(SDL_Point point)
{
	for (int i = 0; i < iCount; i++)
	{
		if (SDL_EnclosePoints(&point, 1, &(lpArr[i].getRect()), NULL))
		{
			return i;
		}
	}
	return -1;
}

cMenu::cMenu(int iCountInput, ...) : background("default")
{
	background.changeImg("Textures/Menu.jpg");
	iCount = iCountInput;
	char** lpText = new char*[iCount];
	char* lpPtr = (char*)&iCountInput + sizeof(int);
	int iMaxLen = 0;
	for (int i = 0; i < iCount; i++)
	{
		int iLen = 0;
		while (*lpPtr != '\0')
		{
			iLen++;
		}
		lpText[i] = new char[iLen + 1];
		strcpy_s(lpText[i], iLen + 1, lpPtr - iLen);
		if (iLen > iMaxLen)
			iMaxLen = iLen;
	}

	lpArr = new cTextObj[iCount];
	for (int i = 0; i < iCount; i++)
	{
		lpArr[i].setFont("a_AlternaSw.ttf");
		lpArr[i].setSize(40);
		lpArr[i].setText(lpText[i]);
		lpArr[i].setPos(320 - iMaxLen * 20, 240 + (i - iCount / 2) * 20); // масштабирование по высоте и ширине
	}

	for (int i = 0; i < iCount; i++)
		delete[] lpText[i];
	delete[] lpText;
}


cMenu::~cMenu()
{
	delete[] lpArr;
}

void cMenu::draw(SDL_Renderer* lpRenderer)
{
	SDL_RenderClear(lpRenderer);
	background.paint(lpRenderer);
	for (int i = 0; i < iCount; i++)
	{
		lpArr[i].paint(lpRenderer);
	}
	SDL_RenderPresent(lpRenderer);
}

int cMenu::choose(SDL_Renderer* lpRenderer)
{
	bool bFlag = false;
	// [TODO] : Сделать пункты меню перемещающимися или "убегающими"
	SDL_Event event;
	SDL_Point click;
	int iResult = -1;
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
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					bFlag = true;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					click.x = event.button.x;
					click.y = event.button.y;
					iResult = check(click);
				}
			}
		}
		if (iResult >= 0)
		{
			bFlag = true;
		}
	}
	return iResult;
}