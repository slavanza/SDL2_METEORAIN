#include "cMenu.h"
#include <cstring>
#include <random>
#include <ctime>


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

void cMenu::move(int* lpX)
{
	int xSpeed = 1;
	static int t = 0;
	if(!t)
	for (int i = 0; i < iCount; i++)
	{
		if (lpX[i] > lpArr[i].getRect().x)
		{
			if ((lpArr[i].getRect().x + xSpeed) > lpX[i])
				lpArr[i].setPos(lpX[i], lpArr[i].getRect().y);
			else
				lpArr[i].setPos(lpArr[i].getRect().x + xSpeed, lpArr[i].getRect().y);
		}
		else
		{
			if ((lpArr[i].getRect().x - xSpeed) < lpX[i])
				lpArr[i].setPos(lpX[i], lpArr[i].getRect().y);
			else
				lpArr[i].setPos(lpArr[i].getRect().x - xSpeed, lpArr[i].getRect().y);
		}
		if (lpX[i] == lpArr[i].getRect().x)
			lpX[i] = rand() % (630 - lpArr[i].getSize() / 2 * strlen(lpArr[i].getText())) + 10;
	}
	++t %= 5;
}

cMenu::cMenu(int iCountInput, char* lpStr, ...) : background("default")
{
	background.setImg("Textures/Menu.jpg");
	iCount = iCountInput;
	char** lpText = new char*[iCount];
	char** lpPtr = &lpStr;
	int iMaxLen = 0;
	for (int i = 0; i < iCount; i++)
	{
		int iLen = 0;
		while (**lpPtr != 0)
		{
			iLen++;
			(*lpPtr)++;
		}
		lpText[i] = new char[iLen + 1];
		strcpy_s(lpText[i], iLen + 1, *lpPtr - iLen);
		lpPtr++;
		if (iLen > iMaxLen)
			iMaxLen = iLen;
	}

	lpArr = new cTextObj[iCount];
	for (int i = 0; i < iCount; i++)
	{
		lpArr[i].setFont("a_AlternaSw.ttf");
		lpArr[i].setSize(40);
		lpArr[i].setText(lpText[i]);
		lpArr[i].setPos(320 - iMaxLen * lpArr[i].getSize() / 2, 240 + (i - iCount / 2) * lpArr[i].getSize()); // масштабирование по высоте и ширине
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
	int* x = new int[iCount];
	srand(time(0));
	for (int i = 0; i < iCount; i++)
	{
		x[i] = rand() % (630 - lpArr[i].getSize() / 2 * strlen(lpArr[i].getText())) + 10;
	}
	while (!bFlag)
	{
		draw(lpRenderer);
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
		move(x);
		if (iResult >= 0)
		{
			bFlag = true;
		}
	}
	delete[] x;
	return iResult;
}