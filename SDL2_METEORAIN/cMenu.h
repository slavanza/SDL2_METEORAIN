#pragma once

#include "cTextObj.h"

class cMenu
{
protected:
	int iCount;
	cTextObj* lpArr;
	cGraphObj background;
	int check(SDL_Point);
	void move(int*);
public:
	cMenu(int, char*, ...);
	~cMenu();
	void draw(SDL_Renderer*);
	int choose(SDL_Renderer*);
};

