#include "cTextObj.h"
#include <cstring>


cTextObj::cTextObj(char* szFont, int iSize, char* szText) : cGraphObj("default")
{
	TTF_Font* fnt = TTF_OpenFont(szFont, iSize);
	SDL_FreeSurface(lpSurface);
	SDL_Color color{ 255, 255, 255 };
	lpSurface = TTF_RenderUTF8_Solid(fnt, szText, color);
	TTF_CloseFont(fnt);
	lpText = new char[strlen(szText) + 1];
	strcpy_s(lpText, strlen(szText), szText);
}

cTextObj::cTextObj(char* szFont, int iSize, char* szText, int x, int y) : cGraphObj("default", x, y)
{
	TTF_Font* fnt = TTF_OpenFont(szFont, iSize);
	SDL_FreeSurface(lpSurface);
	SDL_Color color{ 255, 255, 255 };
	lpSurface = TTF_RenderUTF8_Solid(fnt, szText, color);
	TTF_CloseFont(fnt);
	lpText = new char[strlen(szText) + 1];
	strcpy_s(lpText, strlen(szText), szText);
}

cTextObj::~cTextObj()
{
	delete[] lpText;
}
