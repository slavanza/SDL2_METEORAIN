#pragma once

#include "cTextObj.h"

class cMenu
{
	int iCount;
	cTextObj* lpArr;
	cGraphObj background;
	int check(SDL_Point);
public:
	cMenu(char*, int, ...);
	~cMenu();
	void draw(SDL_Renderer*);
	int choose(SDL_Renderer*);
};

