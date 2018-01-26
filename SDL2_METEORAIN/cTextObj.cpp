#include "cTextObj.h"
#include <cstring>


void cTextObj::render()
{
	TTF_Font* lpFnt = TTF_OpenFont(lpFont, iSize);
	if (lpSurface)
		SDL_FreeSurface(lpSurface);
	lpSurface = TTF_RenderUTF8_Solid(lpFnt, lpText, color);
	TTF_CloseFont(lpFnt);
	rect.h = lpSurface->h;
	rect.w = lpSurface->w;
}

cTextObj::cTextObj(char* szFont, int iSizeInput, char* szText) : cGraphObj("default")
{
	iSize = iSizeInput;
	color.r = color.g = color.b = color.a = 255;
	lpText = new char[strlen(szText) + 1];
	lpFont = new char[strlen(szFont) + 1];
	lpText[strlen(szText)] = lpFont[strlen(szFont)] = 0;
	strcpy_s(lpText, strlen(szText), szText);
	strcpy_s(lpFont, strlen(szFont), szFont);
	render();
}

cTextObj::cTextObj(char* szFont, int iSizeInput, char* szText, int x, int y) : cGraphObj("default", x, y)
{
	iSize = iSizeInput;
	color.r = color.g = color.b = color.a = 255;
	lpText = new char[strlen(szText) + 1];
	lpFont = new char[strlen(szFont) + 1];
	lpText[strlen(szText)] = lpFont[strlen(szFont)] = 0;
	strcpy_s(lpText, strlen(szText), szText);
	strcpy_s(lpFont, strlen(szFont), szFont);
	render();
}

cTextObj::~cTextObj()
{
	delete[] lpText;
	delete[] lpFont;
}

void cTextObj::changeImg(char* szText)
{
	int w = lpSurface->w, h = lpSurface->h;
	setText(szText);
	render();
	rect.x += (w - rect.w) / 2;
	rect.y += (h - rect.h) / 2;
}

void cTextObj::setColor(int iR, int iG, int iB, int iA)
{
	color.r = iR;
	color.g = iG;
	color.b = iB;
	color.a = iA;
	render();
}

void cTextObj::setSize(int iSizeInput)
{
	iSize = iSizeInput;
	render();
}

void cTextObj::setText(char* szText)
{
	delete[] lpText;
	lpText = new char[strlen(szText) + 1];
	lpText[strlen(szText)] = 0;
	strcpy_s(lpText, strlen(szText), szText);
	render();
}

void cTextObj::setFont(char* szFont)
{
	delete[] lpFont;
	lpFont = new char[strlen(szFont) + 1];
	lpFont[strlen(szFont)] = 0;
	strcpy_s(lpFont, strlen(szFont), szFont);
	render();
}