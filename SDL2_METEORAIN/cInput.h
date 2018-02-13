#pragma once

#include <SDL.h>
#include "cTextObj.h"

class cInput
{
	cGraphObj background;
	cTextObj title;
	char szBuf[21];
public:
	cInput();
	cInput(char*);
	~cInput();
	void setTitle(char*);
	char* input(SDL_Renderer*);
	void draw(SDL_Renderer*);
};

