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

cMenu::cMenu(int iCountInput, char* lpStr, ...) : background("Textures/Menu.jpg"), title("a_AlternaSw.ttf", 50)
{
	title.setColor(238, 221, 130);
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
		lpArr[i].setPos(320 - iMaxLen * lpArr[i].getSize() / 4, 240 + (i - iCount / 2) * lpArr[i].getSize()); // масштабирование по высоте и ширине
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
	background.paint(lpRenderer);
	title.paint(lpRenderer);
	for (int i = 0; i < iCount; i++)
	{
		lpArr[i].paint(lpRenderer);
	}
	SDL_RenderPresent(lpRenderer);
}

int cMenu::choose(SDL_Renderer* lpRenderer)
{
	bool bFlag = false;
	SDL_Event event;
	SDL_Point click;
	int iResult = -1;
	int* x = new int[iCount];
	srand(time(0));
	for (int i = 0; i < iCount; i++)
	{
		x[i] = rand() % (630 - lpArr[i].getRect().w) + 10;
	}
	static int a = -1;
	static unsigned r = rand() % 256, g = rand() % 256, b = rand() % 256;
	while (!bFlag)
	{
		if (!a)
		{
			SDL_Color color = title.getColor();
			if ((color.r != r) && (color.g != g) && (color.b != b))
			{
				if (color.r < r)
					color.r++;
				else
					color.r--;
				if (color.g < g)
					color.g++;
				else
					color.g--;
				if (color.b < b)
					color.b++;
				else
					color.b--;
			}
			else
			{
				r = rand() % 256;
				g = rand() % 256;
				b = rand() % 256;
			}
			title.setColor(color.r, color.g, color.b);
		}
		++a %= 10;
		draw(lpRenderer);
		SDL_Point cur;
		SDL_GetMouseState(&cur.x, &cur.y);
		int n = check(cur);
		for (int i = 0; i < iCount; i++)
		{
			if (i != n)
			{
				lpArr[i].setColor();
			}
			else
			{
				lpArr[i].setColor(128, 128, 128);
			}
		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					bFlag = true;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
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

void cMenu::setTitle(char* szTitle)
{
	title.setText(szTitle);
	title.setPos(320 - title.getRect().w / 2, 10);
}