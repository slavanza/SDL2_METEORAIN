#pragma once

#include "cTextObj.h"
#include "cRecords.h"
#include "cMenu.h"

class cRecordsMenu : public cMenu
{
	cGraphObj background;
	cRecords records;
	cTextObj description[4];
	cTextObj names[10];
	cTextObj levels[10];
	cTextObj times[10];
	cTextObj scores[10];
public:
	cRecordsMenu();
	~cRecordsMenu();
	void draw(SDL_Renderer*);
	void choose(SDL_Renderer*);
};

