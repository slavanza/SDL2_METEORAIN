#pragma once

#include "cTextObj.h"

enum msgType {MSG_OK, MSG_YESNO, MSG_INFO};

class cMessage
{
	cGraphObj background;
	cTextObj message;
	cTextObj* buttons;
	msgType type;
public:
	cMessage(char*, msgType);
	~cMessage();
	int show(SDL_Renderer*, unsigned = 0);
	void draw(SDL_Renderer*);
};

