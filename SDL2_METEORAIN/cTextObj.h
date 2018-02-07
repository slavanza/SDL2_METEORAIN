#pragma once

#include <SDL_ttf.h>
#include "cGraphObj.h"

class cTextObj : public cGraphObj
{
	char* lpText;
	char* lpFont;
	int iSize;
	SDL_Color color;
	void render();
public:
	cTextObj();
	cTextObj(char*, int, char* = nullptr);
	cTextObj(char*, int, char*, int, int);
	~cTextObj();
	void changeImg(char*);
	void setColor(int = 255, int = 255, int = 255, int = 255);
	void setSize(int);
	void setText(char*);
	void setFont(char*);
	char* getText();
	int getSize();
	SDL_Color getColor();
};
