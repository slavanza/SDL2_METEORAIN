#pragma once

#include <SDL_ttf.h>
#include "cGraphObj.h"

class cTextObj : public cGraphObj
{
	char* lpText;
	char* lpFont;
	int iSize;
	SDL_Color color;
public:
	cTextObj(char*, int, char*);
	cTextObj(char*, int, char*, int, int);
	~cTextObj();
	void changeImg(char*);
	void setColor(int = 255, int = 255, int = 255, int = 255);
};
