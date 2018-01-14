#pragma once

#include <SDL_ttf.h>
#include "cGraphObj.h"

class cTextObj : public cGraphObj
{
	char* lpText;
public:
	cTextObj(char*, int, char*);
	cTextObj(char*, int, char*, int, int);
	~cTextObj();
};

