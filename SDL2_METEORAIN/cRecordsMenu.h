#pragma once

#include "cTextObj.h"
#include "cRecords.h"

class cRecordsMenu
{
	cGraphObj background;
	cTextObj title;
	cRecords records;
	cTextObj description[4];
	cTextObj names[10];
	cTextObj levels[10];
	cTextObj times[10];
	cTextObj scores[10];
	cTextObj tip;
public:
	cRecordsMenu();
	~cRecordsMenu();
	void draw(SDL_Renderer*);
	void show(SDL_Renderer*);
};

