#include "cTextObj.h"
#include <cstring>


cTextObj::cTextObj(char* szFont, int iSizeInput, char* szText) : cGraphObj("default")
{
	iSize = iSizeInput;
	TTF_Font* lpFnt = TTF_OpenFont(szFont, iSize);
	SDL_FreeSurface(lpSurface);
	color.r = color.g = color.b = color.a = 255;
	lpSurface = TTF_RenderUTF8_Solid(lpFnt, szText, color);
	TTF_CloseFont(lpFnt);
	rect.h = lpSurface->h;
	rect.w = lpSurface->w;
	lpText = new char[strlen(szText) + 1];
	lpFont = new char[strlen(szFont) + 1];
	lpText[strlen(szText)] = lpFont[strlen(szFont)] = 0;
	strcpy_s(lpText, strlen(szText), szText);
	strcpy_s(lpFont, strlen(szFont), szFont);
}

cTextObj::cTextObj(char* szFont, int iSizeInput, char* szText, int x, int y) : cGraphObj("default", x, y)
{
	iSize = iSizeInput;
	TTF_Font* lpFnt = TTF_OpenFont(szFont, iSize);
	SDL_FreeSurface(lpSurface);
	color.r = color.g = color.b = color.a = 255;
	lpSurface = TTF_RenderUTF8_Solid(lpFnt, szText, color);
	TTF_CloseFont(lpFnt);
	rect.h = lpSurface->h;
	rect.w = lpSurface->w;
	lpText = new char[strlen(szText) + 1];
	lpFont = new char[strlen(szFont) + 1];
	lpText[strlen(szText)] = lpFont[strlen(szFont)] = 0;
	strcpy_s(lpText, strlen(szText), szText);
	strcpy_s(lpFont, strlen(szFont), szFont);
}

cTextObj::~cTextObj()
{
	delete[] lpText;
	delete[] lpFont;
}

void cTextObj::changeImg(char* szText)
{
	TTF_Font* lpFnt = TTF_OpenFont(lpFont, iSize);
	int w = lpSurface->w, h = lpSurface->h;
	SDL_FreeSurface(lpSurface);
	color.r = color.g = color.b = color.a = 255;
	lpSurface = TTF_RenderUTF8_Solid(lpFnt, szText, color);
	TTF_CloseFont(lpFnt);
	rect.h = lpSurface->h;
	rect.w = lpSurface->w;
	rect.x += (w - rect.w) / 2;
	rect.y += (h - rect.h) / 2;
	delete[] lpText;
	lpText = new char[strlen(szText) + 1];
	lpText[strlen(szText)] = 0;
	strcpy_s(lpText, strlen(szText), szText);
}

void cTextObj::setColor(int iR, int iG, int iB, int iA)
{
	color.r = iR;
	color.g = iG;
	color.b = iB;
	color.a = iA;
}