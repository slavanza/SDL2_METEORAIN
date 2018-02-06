#pragma once

#include <SDL.h>
#undef main

class cMain
{
	SDL_Window* lpWindow;
	SDL_Renderer* lpRenderer;
public:
	cMain();
	~cMain();
	int main();
};

