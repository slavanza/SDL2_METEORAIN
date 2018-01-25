#include "cGraphObj.h"
#include <SDL_image.h>
#include <iostream>


cGraphObj::cGraphObj(char* szName)
{
	if (!strcmp(szName, "default"))
	{
		lpSurface = nullptr;
		rect.x = rect.y = rect.w = rect.h = 0;
	}
	else
	{
		lpSurface = IMG_Load(szName);
		rect.w = lpSurface->w;
		rect.h = lpSurface->h;
		rect.x = rect.y = 0;
	}
}

cGraphObj::cGraphObj(char* szName, int x, int y)
{
	if (!strcmp(szName, "default"))
	{
		lpSurface = nullptr;
		rect.x = rect.y = rect.w = rect.h = 0;
	}
	else
	{
		lpSurface = IMG_Load(szName);
		rect.x = x;
		rect.y = y;
		rect.w = lpSurface->w;
		rect.h = lpSurface->h;
	}
}

cGraphObj::cGraphObj(const cGraphObj& copy)
{
	lpSurface = SDL_CreateRGBSurface(0, copy.lpSurface->w, copy.lpSurface->h, copy.lpSurface->format->BitsPerPixel, copy.lpSurface->format->Rmask, copy.lpSurface->format->Gmask, copy.lpSurface->format->Bmask, copy.lpSurface->format->Amask);
	SDL_BlitSurface(copy.lpSurface, NULL, lpSurface, NULL);
	rect = copy.rect;
}

cGraphObj::~cGraphObj()
{
	SDL_FreeSurface(lpSurface);
}

SDL_Rect cGraphObj::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
	return rect;
}

SDL_Rect cGraphObj::setSize(int w, int h)
{
	rect.w = w;
	rect.h = h;
	return rect;
}

SDL_Texture* cGraphObj::makeTexture(SDL_Renderer* lpRenderer)
{
	return SDL_CreateTextureFromSurface(lpRenderer, lpSurface);
}

SDL_Rect cGraphObj::getRect()
{
	return rect;
}

void cGraphObj::paint(SDL_Renderer* lpRenderer)
{
	SDL_Texture* lpTexture = SDL_CreateTextureFromSurface(lpRenderer, lpSurface);
	SDL_RenderCopy(lpRenderer, lpTexture, NULL, &rect);
	SDL_DestroyTexture(lpTexture);
}

cGraphObj cGraphObj::operator=(const cGraphObj& copy)
{
	if (lpSurface)
		SDL_FreeSurface(lpSurface);
	lpSurface = SDL_CreateRGBSurface(0, copy.lpSurface->w, copy.lpSurface->h, copy.lpSurface->format->BitsPerPixel, copy.lpSurface->format->Rmask, copy.lpSurface->format->Gmask, copy.lpSurface->format->Bmask, copy.lpSurface->format->Amask);
	SDL_BlitSurface(copy.lpSurface, NULL, lpSurface, NULL);
	rect = copy.rect;
	return *this;
}

void cGraphObj::changeImg(char* szName)
{
	int w = rect.w, h = rect.h;
	if (lpSurface)
		SDL_FreeSurface(lpSurface);
	lpSurface = IMG_Load(szName);
	rect.w = lpSurface->w;
	rect.h = lpSurface->h;
	rect.x += (w - rect.w) / 2;
	rect.y += h - rect.h;
}