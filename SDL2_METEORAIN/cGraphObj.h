#pragma once

#include <SDL.h>
#include <SDL_image.h>

class cGraphObj
{
	SDL_Surface* lpSurface;
protected:
	SDL_Rect rect;
public:
	cGraphObj(char*);
	cGraphObj(char*, int, int);
	cGraphObj(const cGraphObj&);
	~cGraphObj();
	SDL_Rect setPos(int, int);
	SDL_Rect setSize(int, int);
	SDL_Texture* makeTexture(SDL_Renderer*);
	virtual void paint(SDL_Renderer*);
	SDL_Rect getRect();
	cGraphObj operator=(const cGraphObj&);
};

