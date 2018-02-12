#include "stdafx.h"
#include "cMain.h"
#include "cGameField.h"
#include "cRecordsMenu.h"

#undef main

bool bSDL_Init = false;
bool bTTF_Init = false;
bool bIMG_Init = false;

void InitAll();
void QuitAll();




int main(int argc, char** argv)
{
	std::cout << "Application started" << std::endl;
	InitAll();
	atexit(QuitAll);

	cMain Game;
	int iReturn = Game.main();
	
	std::cout << "Applicaion ended" << std::endl;
	QuitAll();
	return iReturn;
}




void InitAll()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(-1);
	}
	std::cout << "[ InitAll ] : SDL Initialized" << std::endl;
	bSDL_Init = true;
	if (TTF_Init() < 0)
	{
		std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
		exit(-2);
	}
	std::cout << "[ InitAll ] : TTF Initialized" << std::endl;
	bTTF_Init = true;
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
	{
		std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
		exit(-3);
	}
	std::cout << "[ InitAll ] : IMG Initialized" << std::endl;
	bIMG_Init = true;
}

void QuitAll()
{
	if (bSDL_Init)
	{
		SDL_Quit();
		std::cout << "[ InitAll ] : SDL Uninitialized" << std::endl;
	}
	if (bTTF_Init)
	{
		TTF_Quit();
		std::cout << "[ InitAll ] : TTF Uninitialized" << std::endl;
	}
	if (bIMG_Init)
	{
		IMG_Quit();
		std::cout << "[ InitAll ] : IMG Uninitialized" << std::endl;
	}
}